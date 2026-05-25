#!/usr/bin/env python3
"""
Joystick bridge for the KFS staff gripper.

This node contains only controller mapping. It publishes a two-channel command to
/kfs_staff_gripper_cmd, which the Arduino aggregator maps to relay 3-4.
"""

import rclpy
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node
from std_msgs.msg import Int32MultiArray

from my_joystick_msgs.msg import Joystick


class KfsStaffGripperJoystickBridgeNode(Node):
    """
    Convert joystick buttons into staff gripper relay commands.

    Default mapping:
      Y: hold relay 3 ON
      R3: hold relay 4 ON

    The mapping is intentionally simple and parameterized because the final KFS
    staff gripper pneumatic sequence still needs real mechanism verification.
    """

    def __init__(self):
        super().__init__("kfs_staff_gripper_joystick_bridge_node")

        self.declare_parameter("relay3_button", "y")
        self.declare_parameter("relay4_button", "r3")
        self.declare_parameter("publish_hz", 20.0)
        self.declare_parameter("input_timeout_sec", 0.3)
        self.declare_parameter("safe_state", [0, 0])

        self.last_joystick_time = None
        self.current_state = self.get_safe_state()

        self.joy_sub = self.create_subscription(
            Joystick,
            "/joystick_data",
            self.joystick_callback,
            10,
        )
        self.cmd_pub = self.create_publisher(Int32MultiArray, "/kfs_staff_gripper_cmd", 10)

        publish_hz = max(float(self.get_parameter("publish_hz").value), 1.0)
        self.publish_timer = self.create_timer(1.0 / publish_hz, self.publish_timer_callback)

        self.get_logger().info("KFS staff gripper joystick bridge initialized")
        self.get_logger().info(
            "Mapping: "
            f"{self.get_parameter('relay3_button').value} -> staff relay 3, "
            f"{self.get_parameter('relay4_button').value} -> staff relay 4"
        )

    def get_safe_state(self):
        """Return the two-channel staff gripper safe state."""
        raw = list(self.get_parameter("safe_state").value)
        safe = [0, 0]
        for index, value in enumerate(raw[:2]):
            safe[index] = 1 if int(value) else 0
        return safe

    def joystick_callback(self, msg):
        """Update staff gripper state from the configured joystick buttons."""
        self.last_joystick_time = self.get_clock().now()
        relay3_button = str(self.get_parameter("relay3_button").value)
        relay4_button = str(self.get_parameter("relay4_button").value)
        self.current_state = [
            1 if self.get_button(msg, relay3_button) else 0,
            1 if self.get_button(msg, relay4_button) else 0,
        ]

    def get_button(self, msg, button_name):
        """Read a boolean button from Joystick by name, returning False if invalid."""
        if not hasattr(msg, button_name):
            self.get_logger().warn(f"Unknown joystick button: {button_name}")
            return False
        return bool(getattr(msg, button_name))

    def publish_timer_callback(self):
        """Refresh command output and fail safe if joystick input times out."""
        state = self.current_state
        if self.is_joystick_timed_out():
            state = self.get_safe_state()
        self.publish_state(state)

    def is_joystick_timed_out(self):
        """Return true when /joystick_data has stopped for input_timeout_sec."""
        if self.last_joystick_time is None:
            return True
        elapsed = (self.get_clock().now() - self.last_joystick_time).nanoseconds / 1e9
        return elapsed > float(self.get_parameter("input_timeout_sec").value)

    def publish_state(self, state):
        """Publish [staff_relay3_state, staff_relay4_state]."""
        cmd = Int32MultiArray()
        cmd.data = [int(state[0]), int(state[1])]
        self.cmd_pub.publish(cmd)


def main(args=None):
    rclpy.init(args=args)
    node = KfsStaffGripperJoystickBridgeNode()
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
