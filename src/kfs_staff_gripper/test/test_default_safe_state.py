"""No-hardware checks for the shared three-relay startup state."""

from kfs_staff_gripper.kfs_staff_gripper_arduino_node import DEFAULT_SAFE_STATE


def test_default_state_matches_confirmed_six_relay_wiring():
    """KFS closes, both arm grippers open, and all heights stay low."""
    assert DEFAULT_SAFE_STATE == [0, 0, 1, 0, 1, 1]
