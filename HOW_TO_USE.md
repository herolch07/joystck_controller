# 使用说明 - 一步一步教你用

## 🚀 第一次使用（快速开始）

### 1. 给脚本添加执行权限（只需要做一次）

```bash
cd /home/robotics/robocon/new_ws
chmod +x start.sh start_background.sh start_ssh.sh stop.sh set_speed.sh
```

---

## 💻 本地使用（在机器人上直接操作）

### 启动系统：
```bash
cd /home/robotics/robocon/new_ws
./start.sh
```

**会发生什么：**
- 自动打开 4 个终端窗口
- 每个窗口显示一个节点的输出
- 可以看到所有日志信息

**停止系统：**
- 在每个窗口按 `Ctrl+C`
- 然后关闭窗口

---

## 🌐 SSH 远程使用（推荐）

### 启动系统：
```bash
ssh robotics@你的机器人IP
cd /home/robotics/robocon/new_ws
./start_background.sh
```

**会发生什么：**
```
==========================================
  启动底盘控制系统 - R2-700
==========================================

✅ 准备启动所有节点...

[1/4] 启动电机驱动节点 (damiao_node)...
      ✅ 电机驱动节点已启动 (PID: 12345)
[2/4] 启动运动学节点 (local_navigation_node)...
      ✅ 运动学节点已启动 (PID: 12346)
[3/4] 启动手柄驱动 (joystick_node)...
      ✅ 手柄驱动已启动 (PID: 12347)
[4/4] 启动手柄桥接 (joystick_bridge)...
      ✅ 手柄桥接已启动 (PID: 12348)

==========================================
✅ 所有节点启动成功！
==========================================

提示: 节点在后台运行，可以安全关闭此终端
```

**启动成功后，你就可以关闭 SSH 了！节点会继续运行。**

### 查看日志（可选）：
```bash
ssh robotics@你的机器人IP
cd /home/robotics/robocon/new_ws

# 实时查看电机驱动日志
tail -f logs/damiao_node.log

# 查看手柄驱动日志
tail -f logs/joystick_node.log

# 按 Ctrl+C 退出查看
```

### 停止系统：
```bash
ssh robotics@你的机器人IP
cd /home/robotics/robocon/new_ws
./stop.sh
```

**会发生什么：**
```
==========================================
  停止底盘控制系统
==========================================

正在停止节点...
停止进程 12345 ...
停止进程 12346 ...
停止进程 12347 ...
停止进程 12348 ...

==========================================
✅ 所有节点已停止
==========================================
```

---

## ⚡ 调整速度（超简单）

### 方法 1：使用速度调整脚本（推荐）

```bash
cd /home/robotics/robocon/new_ws
./set_speed.sh
```

**会显示：**
```
==========================================
  底盘速度调整工具
==========================================

✅ 检测到 joystick_bridge 节点正在运行

📊 当前设置：
   最大速度:   100.0 cm/s
   最大旋转:   2.0 rad/s

==========================================
选择速度等级：
==========================================
1. 慢速   - 100 cm/s (1 m/s)   - 测试/调试用
2. 中速   - 150 cm/s (1.5 m/s) - 正常练习
3. 快速   - 200 cm/s (2 m/s)   - 比赛速度
4. 极速   - 300 cm/s (3 m/s)   - 最大性能（谨慎）
5. 自定义 - 手动输入速度
0. 退出

请选择 [0-5]: 
```

**选择一个数字，按回车，立即生效！**

例如：
- 按 `3` 然后回车 → 速度变为 200 cm/s（快速）
- 按 `2` 然后回车 → 速度变为 150 cm/s（中速）

### 方法 2：手动调整（高级用户）

```bash
# 设置速度为 200 cm/s
ros2 param set /joystick_bridge max_speed_cm 200.0

# 设置旋转速度为 3 rad/s
ros2 param set /joystick_bridge max_rotation 3.0

# 查看当前速度
ros2 param get /joystick_bridge max_speed_cm
```

**立即生效，无需重启！**

---

## 🛡️ 安全性说明

### **手柄断开会怎样？**

**情况 1：手柄蓝牙断开**
```
1. 手柄断开
   ↓
2. joystick_node 检测到断开（< 100ms）
   ↓
3. 所有轴归零，发布 [0, 0, 0, ...]
   ↓
4. 机器人停止
```
**总时间：< 150ms**

**情况 2：joystick_node 崩溃**
```
1. joystick_node 崩溃
   ↓
2. joystick_bridge 超过 500ms 未收到数据
   ↓
3. 看门狗触发，发送停止指令 [0, 0, 0]
   ↓
4. 机器人停止
```
**总时间：< 600ms**

**结论：✅ 非常安全！机器人不会暴走！**

---

## 🎮 手柄控制说明

### 左摇杆：控制底盘平移
- 向上推 → 前进
- 向下推 → 后退
- 向左推 → 左平移
- 向右推 → 右平移
- 斜向推 → 斜向移动
- 推得越远 → 速度越快（最大速度受 max_speed_cm 限制）

### 右摇杆（左右）：控制底盘旋转
- 向右推 → 顺时针旋转
- 向左推 → 逆时针旋转
- 推得越远 → 旋转越快（最大旋转受 max_rotation 限制）

### 同时操作：
- 可以同时推动左右摇杆 → 边移动边旋转

---

## 🔧 常见问题

### Q1：如何确认系统是否启动成功？

**A1：** 运行以下命令查看所有节点：
```bash
ros2 node list
```

**应该看到：**
```
/damiao_node
/joystick_bridge
/joystick_node
/local_navigation_node
```

如果看到这 4 个节点，说明启动成功！

---

### Q2：如何查看手柄是否连接？

**A2：** 查看手柄驱动日志：
```bash
tail -f logs/joystick_node.log
```

**正常应该看到：**
```
[INFO] Auto-detected device: 8BitDo Pro 2
```

**如果没有：**
```
[WARN] No device found with filter '8BitDo'
```
检查手柄是否开机并配对。

---

### Q3：机器人不动怎么办？

**A3：** 按顺序检查：

1. **确认所有节点都在运行：**
```bash
ros2 node list
```

2. **查看手柄数据是否发布：**
```bash
ros2 topic echo /joystick_data
```
推动摇杆，应该看到数值变化。

3. **查看底盘指令是否发布：**
```bash
ros2 topic echo /local_driving
```
推动摇杆，应该看到 `[方向, 速度, 旋转]` 变化。

4. **查看电机是否使能：**
```bash
tail -f logs/damiao_node.log
```
应该看到 `isEnable=True`

---

### Q4：速度调整后重启会恢复吗？

**A4：** 会的！

- 用 `./set_speed.sh` 或 `ros2 param set` 调整的速度只是临时的
- 重启节点后会恢复默认值（100 cm/s）

**如果想永久改变默认速度：**
修改启动脚本，在启动 joystick_bridge 时添加参数：
```bash
ros2 run joystick_bridge joystick_bridge --ros-args \
  -p max_speed_cm:=200.0 \
  -p max_rotation:=3.0
```

---

### Q5：SSH 断开后节点会停止吗？

**A5：** 不会！

- 用 `./start_background.sh` 启动的节点在后台运行
- SSH 断开后节点继续运行
- 可以安全地关闭 SSH 连接

---

### Q6：如何查看实时速度？

**A6：** 
```bash
# 查看底盘指令（包含当前速度）
ros2 topic echo /local_driving

# 查看手柄原始数据
ros2 topic echo /joystick_data
```

---

## 📊 完整命令速查表

| 操作 | 命令 |
|-----|------|
| **启动（本地）** | `./start.sh` |
| **启动（SSH）** | `./start_background.sh` |
| **停止** | `./stop.sh` |
| **调整速度** | `./set_speed.sh` |
| **查看节点** | `ros2 node list` |
| **查看话题** | `ros2 topic list` |
| **查看日志** | `tail -f logs/damiao_node.log` |
| **手动设速度** | `ros2 param set /joystick_bridge max_speed_cm 200.0` |
| **查看当前速度** | `ros2 param get /joystick_bridge max_speed_cm` |

---

## 🎯 推荐的使用流程

### **日常使用（SSH 远程）：**

```bash
# 1. SSH 连接到机器人
ssh robotics@你的机器人IP

# 2. 进入工作目录
cd /home/robotics/robocon/new_ws

# 3. 启动系统
./start_background.sh

# 4. （可选）调整速度
./set_speed.sh

# 5. 关闭 SSH，开始使用手柄控制机器人

# 6. 用完后，SSH 连接回来停止系统
./stop.sh
```

**就这么简单！** 🎉

---

**更新日期：** 2026-02-02  
**版本：** v2.0 - 添加超时保护和速度调整工具
