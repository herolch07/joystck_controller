#!/usr/bin/env python3
"""
Keyboard operator teleop node.

This node is an operator-input bridge for temporary testing when a game
controller is unavailable. It publishes the same subsystem command topics that
the joystick bridge nodes normally publish, but it does not contain hardware
driver logic, motor protocol logic, or competition strategy.

Applicable scope:
- Holonomic base command topic using /local_driving
- Speed-command mechanisms using one-value Float32MultiArray topics
- Two-relay pneumatic gripper command topic using /pneumatic_gripper_cmd
"""

import math
import select
import sys
import termios
import time
import tty

import rclpy
from rclpy.executors import ExternalShutdownException
from rclpy.node import Node
from std_msgs.msg import Float32MultiArray, Int32MultiArray


class KeyboardTeleopNode(Node):
    """
    Convert interactive keyboard input into existing robot command topics.

    The node is intentionally interface-based: it publishes topics only and does
    not inspect or depend on the internals of base, arm, or pneumatic driver
    nodes. Key presses are treated as short-lived commands; if a key stops
    repeating, the command naturally returns to zero after key_hold_sec.
    """

    def __init__(self):
        super().__init__("keyboard_teleop_node")

        self.declare_parameter("publish_hz", 20.0)
        self.declare_parameter("key_hold_sec", 0.25)
        self.declare_parameter("base_speed_cm", 25.0)
        self.declare_parameter("base_rotation_rad_s", 1.0)
        self.declare_parameter("elevator_speed_rad_s", 1.0)
        self.declare_parameter("horizontal_speed_rad_s", 4.0)
        self.declare_parameter("arm_gripper_speed_rad_s", 0.5)
        self.declare_parameter("initial_pneumatic_height", 0)

        self.local_driving_pub = self.create_publisher(
            Float32MultiArray, "/local_driving", 10
        )
        self.elevator_pub = self.create_publisher(
            Float32MultiArray, "/elevator_speed_cmd", 10
        )
        self.horizontal_pub = self.create_publisher(
            Float32MultiArray, "/horizontal_speed_cmd", 10
        )
        self.arm_gripper_pub = self.create_publisher(
            Float32MultiArray, "/arm_gripper_speed_cmd", 10
        )
        self.pneumatic_pub = self.create_publisher(
            Int32MultiArray, "/pneumatic_gripper_cmd", 10
        )

        self.active_until = {}
        self.pneumatic_height = (
            1 if int(self.get_parameter("initial_pneumatic_height").value) else 0
        )
        self.print_controls()

    def print_controls(self):
        """Print the operator key map to the ROS log."""
        self.get_logger().info(
            "Keyboard teleop ready. Focus this terminal and hold keys; SPACE stops."
        )
        self.get_logger().info("Base: W/S forward/back, A/D left/right, Q/E rotate")
        self.get_logger().info("Elevator: I/K. Horizontal: J/L. Arm gripper motor: U/O")
        self.get_logger().info("Pneumatic: B open while held, H height high, N height low")
        self.get_logger().info("Other: SPACE stop all, ? help, Ctrl+C quit")

    def handle_key(self, key):
        """
        Update active command state from one keyboard character.

        Movement keys are edge-lightweight: every received key extends that
        action for key_hold_sec. If the terminal stops producing repeats, the
        publisher loop automatically returns that axis to zero.
        """
        now = time.monotonic()
        hold_sec = float(self.get_parameter("key_hold_sec").value)
        key_lower = key.lower()

        if key == " ":
            self.active_until.clear()
            self.publish_all_stop()
            self.get_logger().info("Stop all keyboard commands")
            return

        if key == "?":
            self.print_controls()
            return

        if key_lower == "h":
            self.pneumatic_height = 1
            self.get_logger().info("Pneumatic height latched HIGH")
            return

        if key_lower == "n":
            self.pneumatic_height = 0
            self.get_logger().info("Pneumatic height latched LOW")
            return

        action = {
            "w": "base_forward",
            "s": "base_back",
            "a": "base_left",
            "d": "base_right",
            "q": "base_rotate_ccw",
            "e": "base_rotate_cw",
            "i": "elevator_positive",
            "k": "elevator_negative",
            "j": "horizontal_negative",
            "l": "horizontal_positive",
            "u": "arm_gripper_negative",
            "o": "arm_gripper_positive",
            "b": "pneumatic_open",
        }.get(key_lower)

        if action:
            self.active_until[action] = now + hold_sec

    def is_active(self, action):
        """Return whether an action is still inside its key_hold_sec window."""
        return time.monotonic() <= self.active_until.get(action, 0.0)

    def publish_commands(self):
        """Publish the current command state to every controlled subsystem."""
        self.publish_base()
        self.publish_single_value(
            self.elevator_pub,
            self.axis_value("elevator_positive", "elevator_negative")
            * float(self.get_parameter("elevator_speed_rad_s").value),
        )
        self.publish_single_value(
            self.horizontal_pub,
            self.axis_value("horizontal_positive", "horizontal_negative")
            * float(self.get_parameter("horizontal_speed_rad_s").value),
        )
        self.publish_single_value(
            self.arm_gripper_pub,
            self.axis_value("arm_gripper_positive", "arm_gripper_negative")
            * float(self.get_parameter("arm_gripper_speed_rad_s").value),
        )
        self.publish_pneumatic()

    def publish_base(self):
        """Publish /local_driving as [direction_rad, speed_cm_s, rotation_rad_s]."""
        forward = self.axis_value("base_forward", "base_back")
        right = self.axis_value("base_right", "base_left")
        rotation = self.axis_value("base_rotate_ccw", "base_rotate_cw")

        magnitude = min(math.sqrt(forward * forward + right * right), 1.0)
        direction = math.atan2(right, forward) if magnitude > 0.0 else 0.0
        speed_cm = magnitude * float(self.get_parameter("base_speed_cm").value)
        rotation_rad_s = rotation * float(self.get_parameter("base_rotation_rad_s").value)

        msg = Float32MultiArray()
        msg.data = [float(direction), float(speed_cm), float(rotation_rad_s)]
        self.local_driving_pub.publish(msg)

    def publish_pneumatic(self):
        """Publish the two-relay pneumatic command state."""
        gripper_state = 0 if self.is_active("pneumatic_open") else 1
        msg = Int32MultiArray()
        msg.data = [gripper_state, self.pneumatic_height]
        self.pneumatic_pub.publish(msg)

    def publish_single_value(self, publisher, value):
        """Publish a one-value speed command topic."""
        msg = Float32MultiArray()
        msg.data = [float(value)]
        publisher.publish(msg)

    def publish_all_stop(self):
        """
        Immediately publish zero/safe command values.

        This is used when SPACE is pressed and during node shutdown. It is also
        compatible with downstream watchdogs, which keep enforcing safe output
        if this node is stopped unexpectedly.
        """
        local = Float32MultiArray()
        local.data = [0.0, 0.0, 0.0]
        self.local_driving_pub.publish(local)

        for publisher in (self.elevator_pub, self.horizontal_pub, self.arm_gripper_pub):
            self.publish_single_value(publisher, 0.0)

        pneumatic = Int32MultiArray()
        pneumatic.data = [1, self.pneumatic_height]
        self.pneumatic_pub.publish(pneumatic)

    def axis_value(self, positive_action, negative_action):
        """Combine two opposite actions into one -1/0/1 axis value."""
        positive = 1.0 if self.is_active(positive_action) else 0.0
        negative = 1.0 if self.is_active(negative_action) else 0.0
        return positive - negative


class RawTerminal:
    """Context manager that reads single keys from an interactive Linux terminal."""

    def __init__(self):
        if not sys.stdin.isatty():
            raise RuntimeError("keyboard_teleop_node must run in an interactive terminal")
        self.settings = termios.tcgetattr(sys.stdin)

    def __enter__(self):
        tty.setcbreak(sys.stdin.fileno())
        return self

    def __exit__(self, exc_type, exc, tb):
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, self.settings)

    def read_key(self):
        """Return one typed key if available; otherwise return None."""
        ready, _, _ = select.select([sys.stdin], [], [], 0.0)
        if not ready:
            return None
        return sys.stdin.read(1)


def main(args=None):
    """Run the keyboard polling loop and ROS publisher loop in one process."""
    rclpy.init(args=args)
    node = KeyboardTeleopNode()
    publish_hz = max(float(node.get_parameter("publish_hz").value), 1.0)
    period = 1.0 / publish_hz

    try:
        with RawTerminal() as keyboard:
            while rclpy.ok():
                key = keyboard.read_key()
                if key:
                    node.handle_key(key)
                node.publish_commands()
                rclpy.spin_once(node, timeout_sec=0.0)
                time.sleep(period)
    except (KeyboardInterrupt, ExternalShutdownException):
        pass
    finally:
        node.publish_all_stop()
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
