"""Tests for Motor 7/8 pneumatic selection and safe values."""

from arduino_pneumatic_driver.pneumatic_gripper_joystick_bridge_node import (
    DEFAULT_ARM_SAFE_STATE,
    PneumaticGripperJoystickBridgeNode,
)


def test_arm_safe_state_matches_relays_two_to_six():
    assert DEFAULT_ARM_SAFE_STATE == [0, 1, 0, 1, 1]


def test_motor7_uses_first_height_and_gripper_pair():
    assert PneumaticGripperJoystickBridgeNode.selected_arm_indices(7) == (0, 1)


def test_motor8_uses_reversed_height_and_gripper_pair():
    assert PneumaticGripperJoystickBridgeNode.selected_arm_indices(8) == (3, 4)


def test_toggle_changes_once_per_press():
    toggle = PneumaticGripperJoystickBridgeNode.apply_toggle
    state, previous = toggle(1, True, False)
    assert (state, previous) == (0, True)
    state, previous = toggle(state, True, previous)
    assert (state, previous) == (0, True)
