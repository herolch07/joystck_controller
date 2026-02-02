# 快速启动指南 - R2-700 全向轮底盘

## 🚀 一键启动（推荐）

### 方法 1：一键启动所有节点

```bash
cd /home/robotics/robocon/new_ws
./start.sh
```

**特点：**
- ✅ 一条命令启动所有节点
- ✅ 自动打开 4 个独立终端窗口
- ✅ 每个窗口显示一个节点的输出
- ✅ 简单直观，无需学习额外工具

---

## 📋 系统节点说明

### 节点列表

| 窗口 | 节点名称 | 功能 | 话题 |
|-----|---------|------|------|
| 1 | `damiao_node` | 电机驱动 | 订阅 `/damiao_control` |
| 2 | `local_navigation_node` | 运动学解算 | 订阅 `/local_driving`，发布 `/damiao_control` |
| 3 | `joystick_node` | 手柄驱动 | 发布 `/joystick_data` |
| 4 | `joystick_bridge` | 坐标转换 | 订阅 `/joystick_data`，发布 `/local_driving` |

---

## 🎮 手柄控制说明

### 控制方式

**左摇杆：** 控制底盘平移
- 向上推 → 前进
- 向下推 → 后退
- 向左推 → 左平移
- 向右推 → 右平移
- 斜向推 → 斜向移动

**右摇杆（左右）：** 控制底盘旋转
- 向右推 → 顺时针旋转
- 向左推 → 逆时针旋转

**组合操作：**
- 同时推动左右摇杆 → 边移动边旋转

---

## 🔍 快速检查

### 1. 检查所有节点是否运行

在任意一个终端窗口运行：
```bash
ros2 node list
```

**预期输出：**
```
/damiao_node
/joystick_bridge
/joystick_node
/local_navigation_node
```

### 2. 检查话题数据流

```bash
# 查看手柄输入
ros2 topic echo /joystick_data

# 查看底盘速度指令
ros2 topic echo /local_driving

# 查看电机控制指令
ros2 topic echo /damiao_control

# 查看话题频率
ros2 topic hz /joystick_data
```

### 3. 检查电机状态

查看窗口 1（电机驱动），观察日志：

**正常输出：**
```log
[DEBUG] Motor 1 updated: q=X.XX, dq=X.XX, tau=X.XX, isEnable=True
[DEBUG] Motor 2 updated: q=X.XX, dq=X.XX, tau=X.XX, isEnable=True
[DEBUG] Motor 3 updated: q=X.XX, dq=X.XX, tau=X.XX, isEnable=True
[DEBUG] Motor 4 updated: q=X.XX, dq=X.XX, tau=X.XX, isEnable=True
```

**关键指标：**
- ✅ `isEnable=True` （所有电机）
- ✅ 没有 `Motor X re-enabled` 循环
- ✅ 没有 `Motor ID 0/12 not in motors_map` 警告

---

## ⚙️ 参数调整

### 调整底盘速度

如果速度太快或太慢：

1. 在窗口 4 按 `Ctrl+C` 停止 `joystick_bridge`
2. 重新启动并设置参数：
```bash
source /home/robotics/robocon/new_ws/install/setup.bash
ros2 run joystick_bridge joystick_bridge --ros-args \
  -p max_speed_cm:=150.0 \
  -p max_rotation:=3.0
```

### 调整摇杆死区

如果摇杆回中后有微小漂移：
```bash
source /home/robotics/robocon/new_ws/install/setup.bash
ros2 run joystick_bridge joystick_bridge --ros-args \
  -p deadzone:=820
```

### 动态查看/修改参数

```bash
# 查看所有参数
ros2 param list /joystick_bridge

# 查看具体参数
ros2 param get /joystick_bridge max_speed_cm

# 动态修改参数（无需重启）
ros2 param set /joystick_bridge max_speed_cm 150.0
```

---

## 🛠️ 故障排除

### 问题 1：手柄未识别

**症状：**
```
[ERROR] No device found with filter '8BitDo'
```

**解决：**
```bash
# 检查手柄连接
ls -l /dev/input/event*
sudo evtest

# 检查权限
sudo usermod -a -G input $USER
# 然后重启系统
```

### 问题 2：电机不响应

**症状：** 推动摇杆，底盘不动

**检查步骤：**
1. 确认电机电源已开启
2. 确认 USB-CAN 适配器已连接（`/dev/ttyACM0`）
3. 查看窗口 0 的日志，确认 `isEnable=True`
4. 检查话题连接：
```bash
ros2 topic hz /local_driving
ros2 topic hz /damiao_control
```

### 问题 3：Motor 3 仍然 re-enabled

**症状：**
```
[INFO] Motor 3 re-enabled (isEnable=False)
```

**解决：**
```bash
# 确认代码已更新
grep "data\[3\] & 0x0F" /home/robotics/robocon/new_ws/src/base_omniwheel_r2_700/base_omniwheel_r2_700/DM_CAN.py

# 重新编译
cd /home/robotics/robocon/new_ws
colcon build --packages-select base_omniwheel_r2_700 --symlink-install
source install/setup.bash

# 重启系统
./start_all_nodes.sh
```

### 问题 4：底盘方向不对

**症状：** 推动摇杆方向与底盘实际运动不符

**解决：** 调整电机方向映射

编辑文件：
```bash
nano /home/robotics/robocon/new_ws/src/base_omniwheel_r2_700/base_omniwheel_r2_700/local_navigation_node.py
```

找到 `MOTOR_DIRECTION` 字典（约第 56-60 行）：
```python
MOTOR_DIRECTION = {
    1: -1,  # 如果方向反了，改为 1
    2: 1,   # 如果方向反了，改为 -1
    3: -1,
    4: 1,
}
```

保存后重新编译：
```bash
cd /home/robotics/robocon/new_ws
colcon build --packages-select base_omniwheel_r2_700
```

---

## 🔧 手动启动（如果不用自动脚本）

如果 `./start.sh` 无法使用，可以在 4 个终端中分别手动运行：

**终端 1：电机驱动**
```bash
source /home/robotics/robocon/new_ws/install/setup.bash
ros2 run base_omniwheel_r2_700 damiao_node
```

**终端 2：运动学节点**
```bash
source /home/robotics/robocon/new_ws/install/setup.bash
ros2 run base_omniwheel_r2_700 local_navigation_node
```

**终端 3：手柄驱动**
```bash
source /home/robotics/robocon/new_ws/install/setup.bash
ros2 run my_joystick_driver joystick_node
```

**终端 4：手柄桥接**
```bash
source /home/robotics/robocon/new_ws/install/setup.bash
ros2 run joystick_bridge joystick_bridge
```

---

## 📊 监控命令

### 实时监控话题

```bash
# 查看话题列表
ros2 topic list

# 查看话题频率
ros2 topic hz /joystick_data
ros2 topic hz /local_driving
ros2 topic hz /damiao_control

# 查看话题内容
ros2 topic echo /joystick_data
ros2 topic echo /local_driving
ros2 topic echo /damiao_control
```

### 查看节点信息

```bash
# 节点列表
ros2 node list

# 节点详细信息
ros2 node info /damiao_node

# 话题连接图
rqt_graph
```

---

## 📚 相关文档

| 文档 | 说明 |
|-----|------|
| `QUICK_START.md` | 本文档 - 快速启动指南 |
| `MOTOR3_FIX_REPORT.md` | Motor 3 问题修复报告 |
| `TESTING_GUIDE.md` | 详细测试流程 |
| `README.md` | 项目总体说明 |
| `src/base_omniwheel_r2_700/README.md` | 底盘控制详细说明 |

---

## ✅ 启动检查清单

启动系统前，请确认：

- [ ] 电机电源已开启
- [ ] USB-CAN 适配器已连接（`/dev/ttyACM0` 存在）
- [ ] 手柄已开机并配对
- [ ] 工作区已编译：`colcon build`
- [ ] 环境已加载：`source install/setup.bash`

启动后，请确认：

- [ ] 4 个 ROS2 节点都在运行
- [ ] 所有电机 `isEnable=True`
- [ ] 没有 `Motor X re-enabled` 循环
- [ ] 手柄操作有响应

---

## 🎯 快速测试

启动系统后，进行以下测试：

1. **手柄数据测试：** 推动左摇杆，观察窗口 2 的输出
2. **坐标转换测试：** 在窗口 4 运行 `ros2 topic echo /local_driving`
3. **电机响应测试：** 推动摇杆，观察窗口 0 的电机数据变化
4. **实际运动测试：** 确认底盘按预期方向移动

---

## 🔄 关闭系统

在每个终端窗口按 `Ctrl+C` 关闭对应的节点。

**建议关闭顺序：**
1. 窗口 4：手柄桥接 (joystick_bridge)
2. 窗口 3：手柄驱动 (joystick_node)
3. 窗口 2：运动学节点 (local_navigation_node)
4. 窗口 1：电机驱动 (damiao_node)

然后关闭所有终端窗口即可。

---

**版本：** v1.0  
**更新日期：** 2026-02-02  
**适用系统：** Robocon 2026 R2 全向轮底盘
