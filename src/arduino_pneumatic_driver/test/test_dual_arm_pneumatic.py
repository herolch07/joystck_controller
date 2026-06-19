"""Tests for the five-relay staff pneumatic command layout."""

from arduino_pneumatic_driver.pneumatic_gripper_joystick_bridge_node import (
    DEFAULT_ARM_SAFE_STATE,
    PneumaticGripperJoystickBridgeNode,
)


def test_arm_safe_state_matches_relays_two_to_five():
    assert DEFAULT_ARM_SAFE_STATE == [1, 0, 1, 0]


def test_motor7_uses_first_gripper_channel():
    assert PneumaticGripperJoystickBridgeNode.selected_gripper_index(7) == 0


def test_motor8_uses_third_gripper_channel():
    assert PneumaticGripperJoystickBridgeNode.selected_gripper_index(8) == 2


def test_selected_inclination_indices():
    assert PneumaticGripperJoystickBridgeNode.selected_inclination_index(7) == 3
    assert PneumaticGripperJoystickBridgeNode.selected_inclination_index(8) == 1


def test_toggle_changes_once_per_press():
    toggle = PneumaticGripperJoystickBridgeNode.apply_toggle
    state, previous = toggle(1, True, False)
    assert (state, previous) == (0, True)
    state, previous = toggle(state, True, previous)
    assert (state, previous) == (0, True)


def test_l3_r3_inclination_indices_remain_available():
    assert PneumaticGripperJoystickBridgeNode.selected_inclination_index(7) == 3
    assert PneumaticGripperJoystickBridgeNode.selected_inclination_index(8) == 1
