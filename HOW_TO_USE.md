# R1 使用说明

本说明面向日常操作。当前完整系统以 `r1_start_base_1_0.sh` 为入口；`start.sh`、`start_background.sh` 只保留为旧底盘 4 节点流程，不建议作为 R1 完整系统首选。

## 日常启动

```bash
ssh robotics@你的机器人IP
cd /home/robotics/robocon/new_ws
source install/setup.bash
./r1_start_base_1_0.sh
```

脚本会进入 tmux。离开但保持运行：

```text
Ctrl+b，然后按 d
```

重新进入：

```bash
tmux attach -t r1_control
```

停止全部：

```bash
tmux kill-session -t r1_control
```

## 手柄要求

- 8BitDo 手柄使用 X 模式。
- 当前 `Joystick.msg` 数值范围为 `-512 .. 512`。
- L2/R2 trigger 范围为 `0 .. 512`。
- 当前死区为 `24`。

检查手柄：

```bash
python3 - <<'PY'
from evdev import InputDevice, list_devices
for path in list_devices():
    d = InputDevice(path)
    print(path, d.name)
PY
```

## 控制方式

```text
左摇杆上/下: 底盘前进/后退
左摇杆左/右: 底盘左/右横移
右摇杆左/右: 底盘原地旋转
R2: Motor 5 elevator 正向
L2: Motor 5 elevator 反向
D-pad 左/右: Motor 6 horizontal 左/右移动
D-pad 上/下: Motor 6 horizontal power level 增加/减少
START/SELECT: 底盘平移速度档位升/降，10/20/60/100/200/400 cm/s
R1: Motor 7 arm gripper 正向
L1: Motor 7 arm gripper 反向
B: pneumatic gripper OPEN，松开 CLOSE
A: pneumatic height HIGH latch
X: pneumatic height LOW latch
```

## 调整底盘速度

当前默认是低速联调值：

```text
max_speed_cm = 20.0
max_rotation = 0.5
```

查看：

```bash
ros2 param get /joystick_bridge max_speed_cm
ros2 param get /joystick_bridge max_rotation
```

临时提高：

```bash
ros2 param set /joystick_bridge max_speed_cm 40.0
ros2 param set /joystick_bridge max_rotation 1.0
```

这些参数是运行时临时值，重启 `joystick_bridge` 后会回到源码默认值。

## 安全保护

当前链路有多层 timeout：

```text
joystick_bridge:
  /joystick_data 超过 0.3s 未更新
  -> /local_driving = [0,0,0]

local_navigation_node:
  /local_driving 超过 0.3s 未更新
  -> Motor 1-4 发送 0 rad/s

damiao_node:
  连续 VEL 命令超过 0.5s 未刷新
  -> 对应 motor_id 发送 0 rad/s

r1_arm_control:
  执行机构 speed_cmd 超过 0.3s 未刷新
  -> 对应 Motor 5/6/7 发送 0 rad/s

arduino_pneumatic_driver:
  /pneumatic_gripper_cmd 超过 0.5s 未刷新
  -> safe_state = [1,0] = CLOSE + LOW
```

## 常用检查

```bash
ros2 node list
ros2 topic list
ros2 topic echo /joystick_data
ros2 topic echo /local_driving
ros2 topic echo /damiao_control
ros2 topic echo /elevator_status
ros2 topic echo /horizontal_status
ros2 topic echo /arm_gripper_status
ros2 topic echo /pneumatic_gripper_status
```

## 如果没有反应

按顺序检查：

1. `tmux attach -t r1_control` 查看对应窗口是否退出。
2. `ros2 node list` 确认节点存在。
3. `ros2 topic echo /joystick_data` 确认手柄数据变化。
4. `ros2 topic echo /local_driving` 确认底盘指令变化。
5. 查看 `motors` 窗口确认达妙驱动已连接。
6. 确认 `/dev/ttyACM0` 是达妙 USB-CAN，Arduino relay 在 `/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0`。
