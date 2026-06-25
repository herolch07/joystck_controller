# Arduino Firmware

This directory stores Arduino-side firmware used by the R1 ROS 2 workspace.

## Five Relay Panel

Sketch:

```text
arduino/five_relay_panel/five_relay_panel.ino
```

Board target:

```text
Arduino Mega / compatible Mega board
Serial baud rate: 9600
```

Current relay protocol:

```text
Serial command format: [r1,r2,r3,r4,r5]
Example: [0,1,0,1,0]
Pin order: {22, 24, 25, 27, 28}
Trigger logic: HIGH = ON, LOW = OFF
```

Current ROS-side meaning:

```text
relay 1 / pin 22: KFS gripper
relay 2 / pin 24: Motor7 STAFF gripper relay
relay 3 / pin 25: Motor8 inclination/head relay
relay 4 / pin 27: Motor8 STAFF gripper relay
relay 5 / pin 28: Motor7 inclination/head relay
```

The current full safe state used by the ROS aggregator is:

```text
[0,1,0,1,0]
```

The ROS node that owns this serial protocol is:

```text
ros2 run kfs_staff_gripper kfs_staff_gripper_arduino_node
```

Do not open the Arduino IDE Serial Monitor while the ROS node is running, because both processes need exclusive access to the same serial port.

## Upload Notes

1. Open `five_relay_panel.ino` with Arduino IDE.
2. Select the correct Arduino Mega board and serial port.
3. Upload the sketch.
4. Close Serial Monitor before starting ROS.
5. Start the ROS workspace through `r1_start_base_1_0.sh`.

## Safety Note

This sketch writes all relay pins to `LOW` before enabling them as outputs during startup. Runtime command-source timeout is handled on the ROS side by `kfs_staff_gripper_arduino_node`, which writes the full safe state on startup, reconnect, shutdown, and command timeout.
