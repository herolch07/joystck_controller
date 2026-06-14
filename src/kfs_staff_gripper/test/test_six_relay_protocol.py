"""Tests for the confirmed six-relay Arduino protocol."""

import pytest

from kfs_staff_gripper.kfs_staff_gripper_arduino_node import (
    DEFAULT_SAFE_STATE,
    format_relay_command,
    normalize_relay_state,
)


def test_confirmed_six_relay_safe_state():
    assert DEFAULT_SAFE_STATE == [0, 0, 1, 0, 1, 1]


def test_serial_line_has_exact_arduino_format():
    assert format_relay_command(DEFAULT_SAFE_STATE) == "[0,0,1,0,1,1]\n"


def test_protocol_rejects_old_three_relay_state():
    with pytest.raises(ValueError):
        normalize_relay_state([0, 0, 0])


def test_protocol_clamps_values_to_binary():
    assert normalize_relay_state([0, 2, -1, 0, 7, 1]) == [0, 1, 1, 0, 1, 1]
