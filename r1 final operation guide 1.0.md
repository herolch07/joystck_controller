# R1 Final Operation Guide 1.0

本指南记录当前可用版本的 R1 底盘启动流程。当前版本已确认：

- 手柄必须使用 X 模式。
- 手柄数据范围是 `-128 ~ 128`，比旧版 `8192` 更容易读。
- `joystick_bridge` 默认最大平移速度是 `40 cm/s`。
- 全向轮半径按 `63.5 mm` 换算电机速度。
- Motor 3 存在硬件/驱动响应问题，当前软件不再强行平滑补偿。

## 0. 启动前检查

确认硬件：

```bash
lsusb
ls -l /dev/ttyACM0
```

手柄需要能在 evdev 里看到：

```bash
cd /home/robotics/robocon/new_ws
source install/setup.bash
python3 - <<'PY'
from evdev import InputDevice, list_devices
for path in list_devices():
    d = InputDevice(path)
    print(path, d.name)
PY
```

正常应看到类似：

```text
8BitDo Ultimate Wireless / Pro 2 Wired Controller
```

如果只在 `lsusb` 里看到 `8BitDo IDLE`，说明手柄还没有作为 controller 连接。把手柄切到 X 模式后重新插入。

## 1. 推荐一键启动

使用新的 tmux 启动脚本：

```bash
cd /home/robotics/robocon/new_ws
chmod +x r1_start_base_1_0.sh
./r1_start_base_1_0.sh
```

脚本会启动 tmux session：

```text
r1_base_control
```

窗口：

```text
0 joystick   手柄驱动
1 bridge     手柄到底盘转换
2 motors     达妙电机驱动
3 nav        全向轮运动学
4 monitor    监控命令窗口
```

tmux 常用操作：

```text
切换窗口: Ctrl+b，然后按 0-4
离开但保持运行: Ctrl+b，然后按 d
重新进入: tmux attach -t r1_base_control
关闭全部: tmux kill-session -t r1_base_control
```

## 2. 手动启动

如果不用脚本，开 4 个 terminal。

Terminal 1:

```bash
cd /home/robotics/robocon/new_ws
source install/setup.bash
ros2 run my_joystick_driver joystick_node
```

Terminal 2:

```bash
cd /home/robotics/robocon/new_ws
source install/setup.bash
python3 -m joystick_bridge.joystick_bridge
```

Terminal 3:

```bash
cd /home/robotics/robocon/new_ws
source install/setup.bash
ros2 run base_omniwheel_r2_700 damiao_node
```

Terminal 4:

```bash
cd /home/robotics/robocon/new_ws
source install/setup.bash
ros2 run base_omniwheel_r2_700 local_navigation_node
```

## 3. 验证节点

```bash
cd /home/robotics/robocon/new_ws
source install/setup.bash
ros2 node list
```

应看到：

```text
/joystick_node
/joystick_bridge
/motor_controller_node
/local_navigation_node
```

## 4. 验证话题

手柄原始数据：

```bash
ros2 topic echo /joystick_data
```

现在手柄范围应是：

```text
lx/ly/rx/ry: -128 ~ 128
l2/r2: 0 ~ 128
```

底盘运动指令：

```bash
ros2 topic echo /local_driving
```

格式：

```text
data[0] = direction_rad
data[1] = speed_cm_per_sec
data[2] = rotation_rad_per_sec
```

电机命令：

```bash
ros2 topic echo /damiao_control
```

格式：

```text
data[0] = motor_id
data[1] = mode, 3 means VEL
data[2] = motor speed rad/s
data[3] = duration, 0 means continuous
```

## 5. 调速度

默认：

```text
max_speed_cm = 40.0
max_rotation = 2.0
deadzone = 6
```

查看：

```bash
ros2 param get /joystick_bridge max_speed_cm
ros2 param get /joystick_bridge max_rotation
ros2 param get /joystick_bridge deadzone
```

设置：

```bash
ros2 param set /joystick_bridge max_speed_cm 40.0
ros2 param set /joystick_bridge max_rotation 1.0
```

更快：

```bash
ros2 param set /joystick_bridge max_speed_cm 60.0
ros2 param set /joystick_bridge max_rotation 1.5
```

当前 Motor 3 状态不理想，不建议直接设置很高速度。

## 6. 控制方式

```text
左摇杆上/下: 前进/后退
左摇杆左/右: 左右平移
右摇杆左/右: 原地旋转
```

所有操作建议先小幅推动摇杆。

## 7. Motor 3 注意事项

Motor 3 已确认存在反向响应慢的问题：

```text
连续反向命令时可以反向
突然从正向切到反向时响应明显慢于其他轮
```

当前判断更像硬件、驱动器参数、接线或 Motor 3 本体问题。当前软件版本不再做强制停车或平滑补偿，因为那些方案影响驾驶手感。

如果需要单独测试电机：

```bash
cd /home/robotics/robocon/new_ws
source install/setup.bash
python3 motor_reversal_test.py --motor 3 --speed 10 --hold 2.0 --repeat 3
```

对比其他电机：

```bash
python3 motor_reversal_test.py --motor 1 --speed 10 --hold 2.0 --repeat 3
python3 motor_reversal_test.py --motor 2 --speed 10 --hold 2.0 --repeat 3
python3 motor_reversal_test.py --motor 4 --speed 10 --hold 2.0 --repeat 3
```

## 8. 停止系统

如果使用 tmux 脚本：

```bash
tmux kill-session -t r1_base_control
```

如果手动启动，在每个 terminal 按：

```text
Ctrl+C
```

如 ROS2 graph 缓存异常：

```bash
ros2 daemon stop
ros2 daemon start
```

## 9. 上传 GitHub

```bash
cd /home/robotics/robocon/new_ws
git status --short
git add .
git commit -m "Add R1 final operation guide and startup script"
git push origin main
```
