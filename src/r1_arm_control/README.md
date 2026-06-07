# r1_arm_control

R1 机械臂控制 package。当前用于控制速度型达妙电机执行机构：升降、水平移动、夹爪。

## 更新记录

### 2026-06-07 v4 Motor 7 混合三次曲线

- Motor 7 的 R2/L2 净输入改为 `y = 0.1x + 0.9x³`。
- 新增 `gripper_linear_weight = 0.1`，允许在 `0.0..1.0` 范围动态调整。
- `max_speed_rad_s = 1.3`、`trigger_deadzone = 24`、topic 和 controller watchdog 均保持不变。
- R2/L2 同时按下时先计算净输入；相同深度仍输出 `0 rad/s`。

### 2026-06-07 v3 升降与机械夹爪按键交换

- Motor 5 升降改为 `R1/L1` 数字按钮固定速度控制。
- `R1` 为升降正向，`L1` 为升降反向，同时按下或同时松开时停止。
- Motor 7 机械夹爪改为 `R2/L2` 模拟扳机控制。
- `R2` 为夹爪正向，`L2` 为夹爪反向，按压深度决定速度。
- Motor 7 旧的 0.5 s 两段速度与 START/SELECT 调速逻辑已移除。
- Motor ID、command topic 和 controller timeout 均不变。

### 2026-05-14 v1 安全版本

- 新增并确认三个执行机构 controller：
  - `elevator_controller_node`
  - `horizontal_controller_node`
  - `arm_gripper_controller_node`
- 新增三个 joystick bridge：
  - `elevator_joystick_bridge_node`
  - `horizontal_joystick_bridge_node`
  - `arm_gripper_joystick_bridge_node`
- 所有 controller 均包含 `timeout_sec` 失效保护。
- 夹爪默认速度降为 `1.0 rad/s`，避免动作过快。

### 2026-06-07 v2 Motor 7 两段式速度（历史记录，已被 v3 覆盖）

- `R1/L1` 按住前 `0.5 s` 使用 `0.3 rad/s`。
- 持续按住超过 `0.5 s` 后切换到高速档，默认 `1.3 rad/s`。
- `START (+)` / `SELECT (-)` 以 `0.1 rad/s` 调整高速档。
- 高速档限制在 `0.3 ~ 1.3 rad/s`。

## 适用范围

本 package 适用于 R1 当前机械臂的速度控制执行机构。node 绑定的是“升降 / 水平 / 夹爪”这类机构职责，不绑定某一年比赛流程或战术状态机。

## Nodes

### elevator_controller_node

订阅：

```text
/elevator_speed_cmd std_msgs/msg/Float32MultiArray
data[0] = target speed, rad/s
```

发布：

```text
/damiao_control std_msgs/msg/Float32MultiArray
data = [motor_id, 3.0, speed_rad_s, 0.0]

/elevator_status std_msgs/msg/Float32MultiArray
data = [target_speed, commanded_speed, timeout_active, motor_id]
```

参数：

```text
motor_id = 5
max_speed_rad_s = 3.0
timeout_sec = 0.3
publish_hz = 20.0
max_accel_rad_s2 = 0.0
```

### horizontal_controller_node

订阅：

```text
/horizontal_speed_cmd std_msgs/msg/Float32MultiArray
data[0] = target speed, rad/s
```

发布：

```text
/damiao_control
/horizontal_status
```

参数：

```text
motor_id = 6
max_speed_rad_s = 20.0
timeout_sec = 0.3
publish_hz = 20.0
max_accel_rad_s2 = 0.0
```

### arm_gripper_controller_node

订阅：

```text
/arm_gripper_speed_cmd std_msgs/msg/Float32MultiArray
data[0] = target speed, rad/s
```

发布：

```text
/damiao_control
/arm_gripper_status
```

参数：

```text
motor_id = 7
max_speed_rad_s = 1.3
timeout_sec = 0.3
publish_hz = 20.0
max_accel_rad_s2 = 0.0
```

## Joystick Bridge Nodes

### elevator_joystick_bridge_node

```text
R1: 升降正向，固定速度
L1: 升降反向，固定速度
R1 + L1: 停止
发布: /elevator_speed_cmd
```

参数：

```text
command_speed_rad_s = 3.0
```

### horizontal_joystick_bridge_node

```text
D-pad 左/右: 水平移动
D-pad 上: 提高速度档 0.2 -> 0.5 -> 1.0
D-pad 下: 降低速度档 1.0 -> 0.5 -> 0.2
发布: /horizontal_speed_cmd
```

### arm_gripper_joystick_bridge_node

```text
R2: 夹爪正向，按压越深速度越高
L2: 夹爪反向，按压越深速度越高
R2 + L2: 先计算两者净输入；相同深度时停止
曲线: y = 0.1x + 0.9x³
发布: /arm_gripper_speed_cmd
```

参数：

```text
max_speed_rad_s = 1.3
trigger_deadzone = 24
gripper_linear_weight = 0.1
trigger range = 0..512
```

理论目标速度（只按一个扳机）：

| 扳机深度 | Motor 7 速度绝对值 |
|---:|---:|
| 10% | 0.014 rad/s |
| 25% | 0.051 rad/s |
| 50% | 0.211 rad/s |
| 75% | 0.591 rad/s |
| 100% | 1.300 rad/s |

## 超时保护

三个 controller 都实现相同的 timeout 逻辑。

触发条件：

```text
超过 timeout_sec 没有收到对应的 speed_cmd topic
```

默认值：

```text
timeout_sec = 0.3 s
```

超时行为：

```text
target_speed = 0.0
继续向 /damiao_control 发布 0 rad/s
status topic 中 timeout_active = 1.0
```

调整示例：

```bash
ros2 param set /elevator_controller_node timeout_sec 0.3
ros2 param set /horizontal_controller_node timeout_sec 0.3
ros2 param set /arm_gripper_controller_node timeout_sec 0.3
```

## 最小启动示例

```bash
cd /home/robotics/robocon/new_ws
source install/setup.bash
ros2 run r1_arm_control arm_gripper_controller_node
```

另一个 terminal 发布测试命令：

```bash
source install/setup.bash
ros2 topic pub /arm_gripper_speed_cmd std_msgs/msg/Float32MultiArray "{data: [0.5]}" --once
```

如果只发布一次，`timeout_sec` 后会自动归零。

## 调试方式

```bash
ros2 topic echo /elevator_status
ros2 topic echo /horizontal_status
ros2 topic echo /arm_gripper_status
ros2 topic echo /damiao_control
```
