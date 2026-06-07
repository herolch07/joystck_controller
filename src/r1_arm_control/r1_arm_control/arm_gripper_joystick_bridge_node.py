#!/usr/bin/env python3
"""Joystick bridge for the R1 mechanical gripper on Motor 7."""

import rclpy
from rclpy.node import Node
from rcl_interfaces.msg import SetParametersResult
from std_msgs.msg import Float32MultiArray
from my_joystick_msgs.msg import Joystick


TRIGGER_MAX = 512.0


class ArmGripperJoystickBridgeNode(Node):
    """Convert L2/R2 analog trigger depth to Motor 7 speed commands.

    R2 commands positive speed and L2 commands negative speed. Pressing both
    produces their signed difference, so equal trigger depths stop the motor.
    The downstream arm gripper controller applies the Motor 7 speed limit and
    command timeout safety behavior.
    """

    def __init__(self):
        super().__init__("arm_gripper_joystick_bridge_node")

        self.declare_parameter("max_speed_rad_s", 1.3)
        self.declare_parameter("trigger_deadzone", 24)
        self.declare_parameter("gripper_linear_weight", 0.1)
        self.add_on_set_parameters_callback(self.parameter_callback)

        self.joy_sub = self.create_subscription(
            Joystick,
            "/joystick_data",
            self.joystick_callback,
            10,
        )
        self.gripper_pub = self.create_publisher(
            Float32MultiArray, "/arm_gripper_speed_cmd", 10
        )

        self.get_logger().info("Arm gripper joystick bridge initialized")
        self.get_logger().info(
            "Mapping: R2 positive, L2 negative; trigger depth controls speed"
        )
        self.get_logger().info(
            "Gripper curve: y = a*x + (1-a)*x^3, "
            f"a={self.get_parameter('gripper_linear_weight').value}"
        )

    def parameter_callback(self, params):
        """Reject invalid runtime curve and speed parameters."""
        for param in params:
            if param.name == "max_speed_rad_s" and float(param.value) <= 0.0:
                return SetParametersResult(
                    successful=False,
                    reason="max_speed_rad_s must be greater than 0",
                )
            if param.name == "gripper_linear_weight":
                weight = float(param.value)
                if not 0.0 <= weight <= 1.0:
                    return SetParametersResult(
                        successful=False,
                        reason="gripper_linear_weight must be in [0.0, 1.0]",
                    )
        return SetParametersResult(successful=True)

    def joystick_callback(self, msg):
        """Publish analog gripper speed from the difference of R2 and L2."""
        max_speed = abs(float(self.get_parameter("max_speed_rad_s").value))
        deadzone = max(0, int(self.get_parameter("trigger_deadzone").value))
        linear_weight = float(self.get_parameter("gripper_linear_weight").value)
        linear_weight = max(0.0, min(linear_weight, 1.0))

        l2 = 0 if msg.l2 < deadzone else min(int(msg.l2), int(TRIGGER_MAX))
        r2 = 0 if msg.r2 < deadzone else min(int(msg.r2), int(TRIGGER_MAX))

        # 先计算两个扳机的净输入，再应用带符号的混合三次曲线。
        normalized_input = max(
            -1.0, min((float(r2) - float(l2)) / TRIGGER_MAX, 1.0)
        )
        curved_input = (
            linear_weight * normalized_input
            + (1.0 - linear_weight) * normalized_input ** 3
        )
        speed = curved_input * max_speed

        cmd = Float32MultiArray()
        cmd.data = [speed]
        self.gripper_pub.publish(cmd)


def main(args=None):
    rclpy.init(args=args)
    node = ArmGripperJoystickBridgeNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
