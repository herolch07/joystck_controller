# 手柄控制链测试指南

## 🧪 测试前准备

### 1. 确认依赖包已编译
```bash
cd /home/robotics/temp/new_ws
colcon build --packages-select my_joystick_msgs my_joystick_driver joystick_bridge
source install/setup.bash
```

### 2. 确认手柄已连接
```bash
# 检查手柄是否被识别
ls -l /dev/input/event*
# 或者
sudo evtest
```

### 3. 确认底盘系统可用
确保 `Robocon2026_r2/2026R2_ws` 已正确编译并可访问。

---

## 🚀 启动测试

### 方法 1：一键启动脚本（推荐）
```bash
cd /home/robotics/temp/new_ws
./start_full_control_chain.sh
```

### 方法 2：手动逐个启动

**终端 1：手柄驱动**
```bash
source /home/robotics/temp/new_ws/install/setup.bash
ros2 run my_joystick_driver joystick_node
```

**终端 2：转换节点**
```bash
source /home/robotics/temp/new_ws/install/setup.bash
ros2 run joystick_bridge joystick_bridge
```

**终端 3：底盘驱动**
```bash
cd /home/robotics/temp/Robocon2026_r2/2026R2_ws
source install/setup.bash
ros2 run base_omniwheel_r2_700 damiao_node
```

**终端 4：导航节点**
```bash
cd /home/robotics/temp/Robocon2026_r2/2026R2_ws
source install/setup.bash
ros2 run base_omniwheel_r2_700 local_navigation_node
```

---

## 🎮 测试步骤

### 1. 基础功能测试

**测试 1：手柄数据读取**
```bash
# 在新终端中查看手柄输出
ros2 topic echo /joystick_data
```
**预期结果：** 推动摇杆时能看到数值变化

**测试 2：转换节点工作**
```bash
# 查看转换后的导航指令
ros2 topic echo /local_driving
```
**预期结果：** 摇杆操作时能看到 `[方向, 速度, 旋转]` 的变化

**测试 3：底盘响应**
```bash
# 查看发送给电机的指令
ros2 topic echo /damiao_control
```
**预期结果：** 应该看到 4 个电机的速度指令

---

### 2. 运动控制测试

**测试序列：**

1. **前进测试**
   - 左摇杆向上推到底
   - 观察：机器人应该向前移动
   - 验证：`/local_driving` 中 speed > 0, direction ≈ 0°

2. **平移测试**
   - 左摇杆向左推到底
   - 观察：机器人应该向左平移
   - 验证：`/local_driving` 中 direction ≈ -90°

3. **旋转测试**
   - 右摇杆向左推
   - 观察：机器人应该逆时针旋转
   - 验证：`/local_driving` 中 rotation > 0

4. **复合运动测试**
   - 左摇杆斜向上推
   - 右摇杆同时向右推
   - 观察：机器人应该边移动边顺时针旋转

5. **停止测试**
   - 所有摇杆回中
   - 观察：机器人应该停止
   - 验证：所有话题数据应该趋于零

---

## 🔍 调试命令

### 实时监控
```bash
# 查看所有相关话题的频率
ros2 topic hz /joystick_data
ros2 topic hz /local_driving
ros2 topic hz /damiao_control

# 查看节点列表
ros2 node list

# 查看话题连接图
rqt_graph
```

### 参数调整
```bash
# 动态调整最大速度
ros2 param set /joystick_bridge max_speed_cm 150.0

# 调整死区
ros2 param set /joystick_bridge deadzone 500
```

### 日志查看
```bash
# 启用调试日志
ros2 run joystick_bridge joystick_bridge --ros-args --log-level debug

# 查看特定节点日志
ros2 run joystick_bridge joystick_bridge --ros-args --log-level INFO
```

---

## ⚠️ 常见问题排查

### 问题 1：手柄无法识别
```
症状：joystick_node 报错找不到设备
解决：
1. 检查蓝牙连接：bluetoothctl
2. 检查权限：sudo usermod -a -G input $USER
3. 查看可用设备：sudo evtest
```

### 问题 2：没有导航指令输出
```
症状：/local_driving 没有数据
可能原因：
1. joystick_bridge 未启动
2. 话题名称不匹配
3. 消息类型不兼容

解决：
ros2 node list  # 确认节点运行
ros2 topic info /joystick_data  # 确认话题存在
```

### 问题 3：机器人不响应
```
症状：有指令但电机不动
检查顺序：
1. damiao_node 是否正常运行
2. USB-CAN 适配器是否连接
3. 电机电源是否开启
4. /damiao_control 是否有数据
```

### 问题 4：运动方向错误
```
症状：推摇杆方向与机器人运动方向不符
解决：
1. 调整 local_navigation_node 中的坐标变换
2. 修改 joystick_bridge 中的方向计算符号
3. 根据实际底盘布局校准参数
```

---

## 📊 测试记录表

| 测试项目 | 预期结果 | 实际结果 | 通过/失败 | 备注 |
|---------|---------|---------|----------|------|
| 手柄连接 | 成功识别设备 | | | |
| 数据读取 | /joystick_data 有输出 | | | |
| 转换功能 | /local_driving 格式正确 | | | |
| 前进运动 | 机器人向前移动 | | | |
| 左平移 | 机器人向左平移 | | | |
| 旋转 | 机器人原地旋转 | | | |
| 复合运动 | 同时平移和旋转 | | | |
| 停止功能 | 摇杆回中时停止 | | | |

---

## 🎯 验收标准

✅ 所有节点能正常启动  
✅ 手柄操作能实时转换为底盘指令  
✅ 机器人能按预期方向和速度运动  
✅ 停止指令能及时生效  
✅ 系统具有基本的安全保护  

---

**测试完成后，请填写测试记录表并提交测试报告！**