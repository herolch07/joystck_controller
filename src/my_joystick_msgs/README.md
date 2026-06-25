# my_joystick_msgs

## Changelog

### 2026-06-25 current interface documentation

- Added this package README so every ROS 2 package has both `README.md` and `TODO.md`.
- Documented the current `Joystick.msg` field ranges and button semantics used by R1.
- Clarified that this package defines message interfaces only; it does not read hardware or publish topics.

## Package 用途

`my_joystick_msgs` 定义 R1 控制系统使用的自定义手柄消息类型。它只负责 ROS 2 interface definition，不包含 node、不读取 evdev、不发布 topic，也不包含任何比赛策略逻辑。

适用范围：

- 8BitDo / Xbox-like gamepad 的标准双摇杆、D-pad、L2/R2、ABXY、肩键、摇杆按键、SELECT/START 输入。
- 当前 R1 手柄链路：`my_joystick_driver` 发布 `/joystick_data`，下游 bridge nodes 订阅该 topic。

## Interfaces

### `msg/Joystick.msg`

消息文件：

```text
src/my_joystick_msgs/msg/Joystick.msg
```

字段定义：

```text
int32 lx
int32 ly
int32 rx
int32 ry
int32 dx
int32 dy
int32 l2
int32 r2

bool a
bool b
bool x
bool y
bool l1
bool r1
bool l3
bool r3
bool select
bool start
```

当前数值约定：

| Field | Range | Meaning |
| --- | --- | --- |
| `lx`, `ly` | `-512 .. 512` | left stick X/Y |
| `rx`, `ry` | `-512 .. 512` | right stick X/Y |
| `dx`, `dy` | `-512 .. 512` | D-pad X/Y after normalization |
| `l2`, `r2` | `0 .. 512` | analog trigger depth |
| `a`, `b`, `x`, `y` | `false/true` | face buttons |
| `l1`, `r1` | `false/true` | shoulder buttons |
| `l3`, `r3` | `false/true` | stick-click buttons; P1/P2 may be controller-side remapped to these |
| `select`, `start` | `false/true` | operation mode buttons |

## Topic 约定

本 package 不创建 publisher 或 subscriber。当前系统约定如下：

| Topic | Type | Publisher | Main subscribers |
| --- | --- | --- | --- |
| `/joystick_data` | `my_joystick_msgs/msg/Joystick` | `my_joystick_driver/joystick_node` | `joystick_bridge`, `operation_mode_selector_node`, mechanism joystick bridge nodes, `joystick_shutdown_node` |

## Timeout / Watchdog

本 package 是 message-only interface package，因此没有运行时 timeout。

需要注意：

- timeout 必须由发布者或订阅者 node 实现。
- 当前系统的 input timeout 主要在 `joystick_bridge`、`operation_mode_control`、`r1_arm_control` bridge nodes、`arduino_pneumatic_driver` bridge nodes 和 `robot_power_control` 中实现。
- 不建议在 message 中加入“隐式安全状态”语义；安全行为应由 node 根据时间戳或接收间隔判断。

## Build

```bash
cd /home/robotics/robocon2026_r1/r1_control_ws
colcon build --packages-select my_joystick_msgs --symlink-install
source install/setup.bash
```

检查 interface：

```bash
ros2 interface show my_joystick_msgs/msg/Joystick
```

## 最小可运行示例

构建后，可以发布一条全零手柄消息：

```bash
ros2 topic pub --once /joystick_data my_joystick_msgs/msg/Joystick \
"{lx: 0, ly: 0, rx: 0, ry: 0, dx: 0, dy: 0, l2: 0, r2: 0, a: false, b: false, x: false, y: false, l1: false, r1: false, l3: false, r3: false, select: false, start: false}"
```

监听：

```bash
ros2 topic echo /joystick_data
```

## 调试方式

- 如果下游 node 找不到 message type，先确认已经 build 并 `source install/setup.bash`。
- 如果 `ros2 interface show my_joystick_msgs/msg/Joystick` 失败，优先检查 `colcon build --packages-select my_joystick_msgs` 是否成功。
- 如果手柄数值范围不符合本文约定，应修改 `my_joystick_driver` 的 normalization，而不是修改 message 字段含义。

## TODO

当前 TODO 维护在 [TODO.md](TODO.md)。重点未完成项：

- [ ] 添加时间戳字段，用于更严格的 input freshness 检测。
- [ ] 添加 controller ID 字段，用于多手柄区分。
- [ ] 如硬件支持，再评估是否加入电池电量或 IMU 字段。
