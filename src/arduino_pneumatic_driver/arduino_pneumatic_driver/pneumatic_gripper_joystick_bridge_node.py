#!/usr/bin/env python3
"""
Joystick bridge for the Arduino pneumatic gripper.

This node maps one controller button to the pneumatic gripper open command.
It contains no serial or hardware logic.
"""

import rclpy
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node
from std_msgs.msg import Int32MultiArray

from my_joystick_msgs.msg import Joystick


class PneumaticGripperJoystickBridgeNode(Node):
    """
    Convert joystick B button into a pneumatic gripper open command.

    Default mapping:
      B: gripper open, D9 = 0, D8 = 1

    D8 is always kept HIGH. Closing is handled by the driver safe_state [1, 1]
    after command timeout, or by manually publishing [1, 1].
    """

    def __init__(self):
        super().__init__("pneumatic_gripper_joystick_bridge_node")

        self.declare_parameter("open_state", [0, 1])

        self.joy_sub = self.create_subscription(
            Joystick,
            "/joystick_data",
            self.joystick_callback,
            10,
        )
        self.cmd_pub = self.create_publisher(Int32MultiArray, "/pneumatic_gripper_cmd", 10)

        self.get_logger().info("Pneumatic gripper joystick bridge initialized")
        self.get_logger().info("Mapping: B open gripper, D8 height kept HIGH")

    def joystick_callback(self, msg):
        """
        Publish the gripper-open command while B is pressed.

        The driver node keeps the safe behavior: if B commands stop arriving,
        it returns to safe_state [1, 1], which means gripper CLOSE + height HIGH.
        """
        if msg.b:
            self.publish_state(self.get_state_parameter("open_state"))

    def normalize_state(self, value):
        """Convert any numeric state parameter to the relay protocol value 0 or 1."""
        return 1 if int(value) else 0

    def get_state_parameter(self, name):
        """Read a two-value relay state parameter and clamp values to 0/1."""
        raw = list(self.get_parameter(name).value)
        if len(raw) < 2:
            return [1, 1]
        return [self.normalize_state(raw[0]), self.normalize_state(raw[1])]

    def publish_state(self, state):
        """Publish [D9_gripper_state, D8_height_state] to the serial driver node."""
        cmd = Int32MultiArray()
        cmd.data = [int(state[0]), int(state[1])]
        self.cmd_pub.publish(cmd)


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
