#!/usr/bin/env python3
"""Joystick bridge for the R1 elevator actuator on Motor 5."""

import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray
from my_joystick_msgs.msg import Joystick


class ElevatorJoystickBridgeNode(Node):
    """Convert L1/R1 digital shoulder buttons to fixed elevator speed commands.

    R1 commands positive speed, L1 commands negative speed, and pressing both or
    neither commands zero. The downstream elevator controller owns Motor 5 and
    applies its command timeout safety behavior.
    """

    def __init__(self):
        super().__init__("elevator_joystick_bridge_node")

        self.declare_parameter("command_speed_rad_s", 3.0)

        self.joy_sub = self.create_subscription(
            Joystick,
            "/joystick_data",
            self.joystick_callback,
            10,
        )
        self.elevator_pub = self.create_publisher(
            Float32MultiArray, "/elevator_speed_cmd", 10
        )

        self.get_logger().info("Elevator joystick bridge initialized")
        self.get_logger().info("Mapping: R1 positive, L1 negative, both stop")

    def joystick_callback(self, msg):
        """Publish a fixed signed speed from the digital shoulder buttons."""
        command_speed = abs(float(self.get_parameter("command_speed_rad_s").value))

        if msg.r1 and not msg.l1:
            speed = command_speed
        elif msg.l1 and not msg.r1:
            speed = -command_speed
        else:
            speed = 0.0

        cmd = Float32MultiArray()
        cmd.data = [speed]
        self.elevator_pub.publish(cmd)


def main(args=None):
    rclpy.init(args=args)
    node = ElevatorJoystickBridgeNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
