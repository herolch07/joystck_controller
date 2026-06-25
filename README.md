# EdUHK Robocon R1 ROS 2 Workspace

Language: English | [简体中文](docs/i18n/README.zh-CN.md) | [繁體中文](docs/i18n/README.zh-TW.md)

This repository is the ROS 2 control workspace for the EdUHK Robocon Robotics Team R1 robot. The current final version is centered on 8BitDo controller operation and covers the omniwheel base, Damiao motors, STAFF gripper, KFS gripper, Arduino five-relay pneumatic panel, autostart, and layered safety watchdogs.

Maintainer: Hero@EdUHK Robotics Team 2026  
GitHub: `herolch07`

## Current Status

This is the current final README for GitHub. The source-of-truth operation and interface documents are:

- [QUICK_START.md](QUICK_START.md): fastest startup and verification steps
- [CONTROLLER_USAGE.md](CONTROLLER_USAGE.md): current controller keymap
- [ARCHITECTURE.md](ARCHITECTURE.md): system architecture and node responsibilities
- [NODE_GRAPH.md](NODE_GRAPH.md): node/topic data flow
- [TESTING_GUIDE.md](TESTING_GUIDE.md): tests and robot-side checks
- [SAFETY_REPORT.md](SAFETY_REPORT.md): safety mechanism summary

Historical documents and early tuning notes are kept only for traceability. They are not the current robot operation reference. The pre-cleanup root README is archived at [docs/history/README.root-before-cleanup.md](docs/history/README.root-before-cleanup.md).

## Naming Note

The correct name is **STAFF gripper**, not arm gripper.

The repository may still contain these legacy names:

- `arm_gripper_controller_node`
- `arm_gripper_joystick_bridge_node`
- `/arm_gripper_speed_cmd`
- `/arm_gripper_status`

Those names belong to the old Motor 7 velocity-control chain and are not used by the current official startup script. The current STAFF gripper chain is:

- Motor 7 / Motor 8 position control: `motor7_position_controller_node`, `motor8_position_controller_node`
- STAFF pneumatic relay: `pneumatic_gripper_joystick_bridge_node`
- Arduino five-relay aggregation: `kfs_staff_gripper_arduino_node`

If the package is renamed later, prefer `src/r1_mechanism_control` over `staff_gripper_control`, because the current `src/r1_arm_control` package also owns Motor 5 elevator and Motor 6 horizontal control.

## Current System

```text
Motor 1-4  : four-wheel omni base, VEL mode
Motor 5    : KFS elevator, VEL mode
Motor 6    : KFS horizontal, VEL mode
Motor 7    : STAFF gripper position motor, POS_VEL mode
Motor 8    : STAFF gripper position motor, POS_VEL mode
Arduino    : five-relay panel for KFS gripper, Motor7/8 STAFF gripper relays, Motor7/8 head/inclination relays
Controller : 8BitDo controller through Linux evdev
```

## Quick Start

On the robot host:

```bash
cd /home/robotics/robocon2026_r1/r1_control_ws
colcon build --symlink-install
source install/setup.bash
chmod +x r1_start_base_1_0.sh
./r1_start_base_1_0.sh
```

The script creates this tmux session:

```text
r1_control
```

Common tmux commands:

```text
Attach: tmux attach -t r1_control
Detach: Ctrl+b, then d
Stop all: tmux kill-session -t r1_control
```

## Runtime Nodes

`r1_start_base_1_0.sh` is the current official startup script. It starts:

```text
joystick_node
operation_mode_selector_node
joystick_bridge
damiao_node
local_navigation_node
elevator_controller_node
elevator_joystick_bridge_node
horizontal_controller_node
horizontal_joystick_bridge_node
motor7_position_controller_node
motor8_position_controller_node
motor_position_selector_joystick_bridge_node
kfs_staff_gripper_arduino_node
pneumatic_gripper_joystick_bridge_node
kfs_staff_gripper_joystick_bridge_node
joystick_shutdown_node
monitor shell
```

Do not use the old `start.sh`, `start_background.sh`, or `start_ssh.sh` as the current official entry point. They are archived under `archive/legacy_scripts/`.

## Controller Keymap

Always active:

```text
Left stick: base translation in operator frame
Right stick: base in-place rotation
D-pad     : set the KFS visual front direction in operator frame
Hold X + Y + B + A for 5 s: Raspberry Pi shutdown
```

Mode select:

```text
SELECT / center-left : STAFF mode (/operation_mode = 1)
START  / center-right: KFS mode   (/operation_mode = 2)
```

STAFF mode:

```text
A     : Motor7 STAFF gripper 90-degree / preset cycle
X     : Motor8 STAFF gripper 90-degree / preset cycle
B     : Motor7 STAFF gripper relay toggle
Y     : Motor8 STAFF gripper relay toggle
R1/R2 : Motor7 trim negative / positive
L1/L2 : Motor8 trim negative / positive
R3/P1 : Motor7 head / inclination relay toggle
L3/P2 : Motor8 head / inclination relay toggle
```

KFS mode:

```text
Y     : KFS gripper toggle
L2/R2 : Motor6 horizontal positive(out) / negative(in)
L1/R1 : Motor5 elevator negative(down) / positive(up)
```

When D-pad down is active, STAFF mode swaps the Motor7/Motor8 STAFF gripper mappings so operation remains intuitive when the operator faces the robot from the opposite side. See [CONTROLLER_USAGE.md](CONTROLLER_USAGE.md) for details.

## Important Defaults

```text
Joystick axis range: -512 .. 512
Trigger range: 0 .. 512
Joystick deadzone: 15

joystick_bridge.max_speed_cm: 150.0
joystick_bridge.max_rotation: 3.0
joystick_bridge.translation_linear_weight: 0.1
joystick_bridge.rotation_linear_weight: 0.1

local_navigation_node.max_wheel_speed_rad_s: 40.0
local_navigation_node.max_wheel_accel_rad_s2: 25.0
local_navigation_node.accel_limit_mode: per_wheel

damiao_node.motor_ids: [1,2,3,4,5,6,7,8]
damiao_node.position_mode_motor_ids: [7,8]
damiao_node.command_timeout_sec: 0.5

Motor5 elevator speed: 28.0 rad/s
Motor6 horizontal speed: 30.0 rad/s
Motor7/Motor8 position presets: [0.0, 32.0, -32.0] rad

STAFF pneumatic safe_state: [1,0,1,0]
Arduino five-relay safe_state: [0,1,0,1,0]
```

Current base calibration:

```text
Motor 1 = left front
Motor 2 = right front
Motor 3 = right rear
Motor 4 = left rear

lateral_axis_sign = 1.0
rotation_axis_sign = 1.0
forward_coeff_1..4   = [1, 1, -1, -1]
lateral_coeff_1..4   = [1, -1, -1, 1]
rotation_coeff_1..4  = [1, -1, 1, -1]
motor_direction_1..4 = [-1, 1, -1, 1]
```

## Package Map

```text
src/my_joystick_msgs          Custom Joystick message
src/my_joystick_driver        evdev controller driver, publishes /joystick_data
src/joystick_bridge           controller-to-/local_driving bridge
src/base_omniwheel_r2_700     omni base kinematics and Damiao motor driver
src/operation_mode_control    STAFF/KFS operation mode selector
src/r1_arm_control            currently R1 mechanism control, owns Motor5/6/7/8 control
src/arduino_pneumatic_driver  STAFF pneumatic bridge, publishes /pneumatic_gripper_cmd
src/kfs_staff_gripper         five-relay Arduino aggregation and KFS gripper bridge
src/keyboard_teleop           keyboard debug entry, not the current match entry
src/robot_power_control       controller long-press shutdown
```

## Safety Layers

The current system has layered timeout/watchdog protection:

- `joystick_bridge`: publishes `/local_driving = [0,0,0]` when `/joystick_data` times out.
- `local_navigation_node`: sends zero speed to Motor 1-4 when `/local_driving` times out.
- `damiao_node`: sends zero speed on motor command timeout; enters recovery when feedback is lost or a motor is disabled; requires a neutral command before non-zero output is unlocked after recovery.
- `r1_arm_control`: Motor5/6 speed controllers zero on timeout; Motor7/8 POS_VEL controllers stop trim and hold the current feedback position on input timeout.
- `operation_mode_control`: publishes `MODE_INVALID` on joystick timeout, causing downstream mechanism bridges to reject stale button state.
- `kfs_staff_gripper_arduino_node`: writes safe state on Arduino serial startup, reconnect, shutdown, and command-source timeout.
- `robot_power_control`: long-press `X+Y+B+A` triggers shutdown; the node supports dry-run by default, while the official startup script passes `dry_run:=false`.

## Autostart

The repository includes a systemd watcher:

```text
systemd/r1-control-autostart.service
scripts/wait_and_start_robot.sh
```

It waits for an 8BitDo / Xbox controller before starting `r1_start_base_1_0.sh`. Current `STOP_ON_CONTROLLER_LOST=0` means a short controller dropout does not kill the tmux session; node watchdogs remain responsible for safe output.

## Cleanup Status

To make the GitHub record easier to read:

- The root README is now the current final entry point.
- Old operation documents were moved to `docs/history/`.
- Old startup scripts were moved to `archive/legacy_scripts/`.
- Hardware debug scripts were moved to `tools/hardware_debug/`.
- `logs/*.log` were removed from Git tracking, and `.gitignore` now includes `logs/`.

## Rename Recommendation

For documentation only, this README already corrects `arm gripper` to `STAFF gripper`.

If the directory or package name is truly changed later, update all of these together:

```text
directory name
package.xml <name>
setup.py package_name
setup.cfg script_dir / install_scripts
Python import path
console_scripts
all ros2 run commands
all documentation and test imports
```

Recommended route:

```text
src/r1_arm_control
  -> src/r1_mechanism_control

r1_arm_control package
  -> r1_mechanism_control
```

Do not rename the whole package to `staff_gripper_control`, because it also owns KFS elevator and KFS horizontal control. Since the system is already in a final state, the lowest-risk cleanup is documentation and legacy-script organization first, not a broad ROS package rename.
