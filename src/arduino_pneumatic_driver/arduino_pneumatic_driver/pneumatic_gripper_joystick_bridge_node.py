#!/usr/bin/env python3
"""Route joystick buttons to two selectable arm pneumatic mechanisms."""

import rclpy
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray, Int32MultiArray

from my_joystick_msgs.msg import Joystick


DEFAULT_ARM_SAFE_STATE = [0, 1, 0, 1, 1]


class PneumaticGripperJoystickBridgeNode(Node):
    """Control Motor 7/8 arm pneumatics using the shared motor selector.

    The command order is Motor7 height/gripper followed by Motor8
    inclination/height/gripper. A and B act on the selected arm. SELECT acts
    only on Motor8 inclination while Motor8 is selected.
    """

    def __init__(self):
        super().__init__("pneumatic_gripper_joystick_bridge_node")

        self.declare_parameter("default_motor_id", 7)
        self.declare_parameter("height_toggle_button", "a")
        self.declare_parameter("gripper_toggle_button", "b")
        self.declare_parameter("inclination_toggle_button", "select")
        self.declare_parameter("safe_state", DEFAULT_ARM_SAFE_STATE)
        self.declare_parameter("publish_hz", 20.0)
        self.declare_parameter("input_timeout_sec", 0.3)

        default_motor = int(self.get_parameter("default_motor_id").value)
        self.selected_motor_id = default_motor if default_motor in (7, 8) else 7
        self.states = self.get_safe_state()
        self.height_toggle_pressed = True
        self.gripper_toggle_pressed = True
        self.inclination_toggle_pressed = True
        self.last_joystick_time = None

        self.joy_sub = self.create_subscription(
            Joystick, "/joystick_data", self.joystick_callback, 10
        )
        self.selector_sub = self.create_subscription(
            Float32MultiArray,
            "/motor_position_selector_status",
            self.selector_status_callback,
            10,
        )
        self.cmd_pub = self.create_publisher(
            Int32MultiArray, "/pneumatic_gripper_cmd", 10
        )

        publish_hz = max(float(self.get_parameter("publish_hz").value), 1.0)
        self.publish_timer = self.create_timer(
            1.0 / publish_hz, self.publish_timer_callback
        )

        self.get_logger().info(
            "Pneumatic bridge initialized: START selects Motor 7/8; "
            "A=selected height, B=selected gripper, "
            "SELECT=Motor 8 inclination"
        )

    def get_safe_state(self):
        """Return five arm relay values in the confirmed wiring order."""
        raw = list(self.get_parameter("safe_state").value)
        safe = list(DEFAULT_ARM_SAFE_STATE)
        for index, value in enumerate(raw[:5]):
            safe[index] = self.normalize_state(value)
        return safe

    def selector_status_callback(self, msg):
        """Track the existing Motor 7/8 selector without handling START twice."""
        if not msg.data:
            return
        selected = int(msg.data[0])
        if selected in (7, 8):
            self.selected_motor_id = selected

    def joystick_callback(self, msg):
        """Apply rising-edge toggles to the currently selected arm."""
        self.last_joystick_time = self.get_clock().now()

        height_pressed = self.get_configured_button(msg, "height_toggle_button")
        gripper_pressed = self.get_configured_button(msg, "gripper_toggle_button")
        inclination_pressed = self.get_configured_button(
            msg, "inclination_toggle_button"
        )

        height_index, gripper_index = self.selected_arm_indices(
            self.selected_motor_id
        )
        self.states[height_index], self.height_toggle_pressed = self.apply_toggle(
            self.states[height_index], height_pressed, self.height_toggle_pressed
        )
        self.states[gripper_index], self.gripper_toggle_pressed = self.apply_toggle(
            self.states[gripper_index], gripper_pressed, self.gripper_toggle_pressed
        )

        if self.selected_motor_id == 8:
            (
                self.states[2],
                self.inclination_toggle_pressed,
            ) = self.apply_toggle(
                self.states[2],
                inclination_pressed,
                self.inclination_toggle_pressed,
            )
        else:
            # Holding SELECT while switching to Motor 8 must not cause a toggle.
            self.inclination_toggle_pressed = inclination_pressed

    @staticmethod
    def normalize_state(value):
        """Clamp a numeric relay value to zero or one."""
        return 1 if int(value) else 0

    @staticmethod
    def selected_arm_indices(motor_id):
        """Return height and gripper command indices for Motor 7 or 8."""
        return (0, 1) if int(motor_id) == 7 else (3, 4)

    @staticmethod
    def apply_toggle(state, pressed, was_pressed):
        """Toggle once on a button rising edge and update edge memory."""
        if pressed and not was_pressed:
            state = 1 - int(state)
        return int(state), bool(pressed)

    @staticmethod
    def apply_height_toggle(height_state, pressed, was_pressed):
        """Backward-compatible alias used by existing unit tests."""
        return PneumaticGripperJoystickBridgeNode.apply_toggle(
            height_state, pressed, was_pressed
        )

    @staticmethod
    def apply_gripper_toggle(gripper_state, pressed, was_pressed):
        """Backward-compatible alias used by existing unit tests."""
        return PneumaticGripperJoystickBridgeNode.apply_toggle(
            gripper_state, pressed, was_pressed
        )

    def get_configured_button(self, msg, parameter_name):
        """Read a parameter-selected Joystick button safely."""
        button_name = str(self.get_parameter(parameter_name).value)
        if not hasattr(msg, button_name):
            self.get_logger().warn(
                f"Unknown pneumatic button: {button_name}",
                throttle_duration_sec=2.0,
            )
            return False
        return bool(getattr(msg, button_name))

    def publish_timer_callback(self):
        """Publish continuously and restore all arm relays after input timeout."""
        if self.is_joystick_timed_out():
            self.states = self.get_safe_state()
            self.height_toggle_pressed = True
            self.gripper_toggle_pressed = True
            self.inclination_toggle_pressed = True

        msg = Int32MultiArray()
        msg.data = [int(value) for value in self.states]
        self.cmd_pub.publish(msg)

    def is_joystick_timed_out(self):
        """Return true after input_timeout_sec without joystick updates."""
        if self.last_joystick_time is None:
            return True
        elapsed = (self.get_clock().now() - self.last_joystick_time).nanoseconds / 1e9
        return elapsed > float(self.get_parameter("input_timeout_sec").value)


def main(args=None):
    rclpy.init(args=args)
    node = PneumaticGripperJoystickBridgeNode()
    try:
        rclpy.spin(node)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
