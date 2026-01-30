# ROS2 Joystick Driver Workspace

这个工作空间实现了一个基于 ROS2 的游戏手柄驱动系统，可以将物理手柄（8BitDo 或其他兼容设备）的输入信号转换为标准化的 ROS2 消息，供机器人控制系统使用。

---

## 📅 项目进度 / Changelog

### v2.1 (2026-01-29) - 规范化改进
**符合 AGENTS.md 工程规范**
- 添加 TODO.md 维护开发任务清单
- README 添加 Changelog 章节记录版本演进
- 超时保护机制文档化（明确说明触发条件和行为）
- 补充 ROS2 接口参考文档

### v2.0 (2026-01-29) - 重大更新
**完整重构手柄驱动系统**
- 🎮 新增 ROS2 参数化配置（auto_detect, device_path, device_name_filter）
- 📊 数据归一化从 float32 (±1.0) 改为 int32 (±8192)
- 🎯 实现死区过滤（410 单位，约 5% 阈值）
- 🛡️ 实现断线自动归零保护
- 🔍 添加详细的设备调试信息
- 🌐 支持多种手柄品牌（8BitDo, Xbox, PS5 等）
- 📖 完整的使用文档和故障排查指南

**破坏性变更：**
- 消息类型从 float32 改为 int32
- 数值范围从 ±1.0 改为 ±8192

### v1.0 (初始版本)
**基础功能实现**
- 基础手柄驱动实现（evdev 库）
- 支持 8BitDo 手柄
- 发布 /joystick_data 话题（20Hz）
- 自动设备检测

---

## 项目结构

```
new_ws/
├── src/
│   ├── my_joystick_msgs/      # 自定义消息定义包
│   │   └── msg/
│   │       └── Joystick.msg   # 手柄数据格式定义
│   └── my_joystick_driver/    # 手柄驱动节点包
│       └── my_joystick_driver/
│           └── joystick_node.py  # 主驱动程序
├── build/                      # 编译输出目录
├── install/                    # 安装目录
└── log/                        # 日志目录
```

---

## 功能概述

### 1. 消息定义 (`my_joystick_msgs`)

定义了手柄数据的标准格式，包含以下字段：

#### 模拟摇杆/扳机（归一化为整数）
- `lx`, `ly`: 左摇杆 X/Y 轴（-8192 到 8192）
- `rx`, `ry`: 右摇杆 X/Y 轴（-8192 到 8192）
- `dx`, `dy`: 方向键 X/Y 轴（-8192, 0, 8192）
- `l2`, `r2`: 左/右扳机（0 到 8192）

#### 数字按键（布尔值）
- `a`, `b`, `x`, `y`: 四个主要按键
- `l1`, `r1`: 左/右肩键
- `l3`, `r3`: 左/右摇杆按下
- `select`, `start`: 选择/开始键

**为什么使用 ±8192 范围？**
- 原始数据范围是 -32768 到 32767（16 位），难以直观理解
- 归一化到 ±8192（13 位精度）提供了：
  - ✅ **更易读**：比原始值小 4 倍，心算更容易
  - ✅ **足够精度**：16384 个离散级别，满足绝大多数控制需求
  - ✅ **整数运算**：避免浮点数舍入误差，性能更好
  - ✅ **兼容性好**：与许多机器人控制库的标准范围一致

**数值示例：**
- `lx = 4096` → 向右推了一半（50%）
- `ly = -8192` → 向下推到底（100%）
- `rx = 0` → 摇杆回中
- `l2 = 6144` → 扳机按下 75%

---

### 2. 驱动节点 (`joystick_node`)

这是核心驱动程序，负责读取硬件信号并发布到 ROS2 话题。

#### 主要功能模块

##### A. 灵活的设备配置（🆕 参数化配置）
支持两种设备连接模式，通过 ROS2 参数动态配置：

**1. 自动检测模式（默认）**
- 自动扫描系统中的 USB/蓝牙输入设备
- 根据设备名称过滤器查找手柄（默认 "8BitDo"）
- 支持自定义过滤器（可用于 Xbox, PS5 等其他手柄）

**2. 手动指定模式**
- 直接指定设备路径（如 `/dev/input/event5`）
- 适用于固定设备路径或使用 udev 规则的场景
- 多手柄系统中可以精确控制每个手柄

**3. 自动重连机制**
- 连接失败时每 1 秒自动重试
- 支持热插拔（断开后会自动重连）

##### B. 后台事件监听（独立线程）
- 使用 `evdev` 库直接读取 Linux 内核的输入事件
- 运行在独立线程中，不阻塞主程序
- 实时捕获每一个按键、摇杆的微小变化

##### C. 数据归一化与映射
将硬件的原始数据转换为标准化数值：

**摇杆映射示例：**
```python
# 原始数据：-32768 到 32767
# 归一化后：-8192 到 8192
左摇杆向右推到底： 32767 → 8192
左摇杆向右推一半： 16384 → 4096
左摇杆回中：         0     → 0
左摇杆向左推一半：  -16384 → -4096
左摇杆向左推到底：  -32768 → -8192
```

**扳机映射示例：**
```python
# 原始数据：0 到 255
# 归一化后：0 到 8192
扳机完全松开：  0   → 0
扳机按一半：    128 → 4096
扳机按到底：    255 → 8192
```

##### D. 死区过滤（Deadzone）
解决摇杆漂移问题：
- 摇杆在物理上无法精确回到绝对零点
- 会产生微小的噪声（如原始值 ±500，归一化后 ±125）
- **解决方案**：设置 410 单位死区（约 5% 的 8192）
  - 当 `|value| < 410` 时，强制归零
  - 只有真正推动摇杆超过 5% 时才输出

**效果对比：**
```
无死区：lx: 125    （微小漂移噪声）
有死区：lx: 0      （干净的零）
```

##### E. 详细的调试信息（🆕 设备列表）
当设备连接失败时，自动打印所有可用的输入设备信息：
```
=== Available Input Devices ===
  Path: /dev/input/event0
  Name: Logitech USB Receiver
  Phys: usb-0000:00:14.0-1/input0
  ---
  Path: /dev/input/event5
  Name: 8BitDo Pro 2
  Phys: usb-0000:00:14.0-3/input0
  ---
===============================
```
帮助快速定位问题：
- 确认手柄是否被系统识别
- 获取正确的设备路径
- 排查权限问题

##### F. 定时发布机制
- 以 20Hz（每 0.05 秒）的频率发布消息
- 即使手柄没有动作，也会持续发布当前状态
- 保证订阅者能及时获取最新数据

##### G. 安全保护机制与超时保护

**问题场景：** 如果手柄突然断电/拔掉，机器人可能会维持最后一个指令（如"前进"），导致失控。

#### 已实现的超时保护（符合 AGENTS.md 规范 9.1）

**1. 硬件断连检测与超时处理**

- **触发条件：** 
  - `OSError` 异常（设备文件 `/dev/input/eventX` 不可读）
  - 通常发生在手柄物理断开、电量耗尽或蓝牙连接丢失时

- **检测机制：**
  - 事件驱动型（实时检测，无延迟）
  - 在后台线程的 `read_loop()` 中捕获异常

- **超时后的行为：**
  1. 立即调用 `_reset_states()`，将所有摇杆和按键状态归零
  2. 发布一条"全零"消息到 `/joystick_data`
  3. 关闭设备句柄（`self.gamepad.close()`）
  4. 进入 2 秒等待后重新尝试连接

- **日志输出：**
  ```
  [ERROR] [joystick_node]: Joystick OSError: {e}. Device may be disconnected.
  [INFO] [joystick_node]: Joystick states reset to safety (all zeros)
  ```

- **代码位置：** `joystick_node.py:141-149`

**2. 节点关闭保护**

- **触发条件：** 
  - 节点被 Ctrl+C 终止
  - `destroy_node()` 被调用

- **行为：**
  1. 调用 `_reset_states()` 归零所有状态
  2. 取消发布定时器
  3. 关闭设备连接
  4. 清理资源

- **代码位置：** `joystick_node.py:197-206`

#### 超时参数配置

| 参数 | 默认值 | 位置 | 说明 |
|------|--------|------|------|
| 重连等待时间 | 2 秒 | `joystick_node.py:149` | 断线后多久尝试重连 |
| 死区阈值 | 410 | `joystick_node.py:42` | 摇杆漂移过滤阈值 |
| 发布频率 | 20 Hz | `joystick_node.py:72` | 定时器周期（0.05 秒） |

**如何修改超时参数：**
```python
# 修改重连等待时间
# 在 joystick_node.py 第 149 行
time.sleep(5)  # 改为 5 秒

# 修改死区阈值（更严格的过滤）
# 在 joystick_node.py 第 42 行
self.deadzone = 820  # 改为 10%
```

#### 未实现的超时保护（推荐在控制端实现）

**发布端超时检测：**
- 本驱动节点作为发布者，无法检测"订阅者是否正常接收"
- 如需实现端到端超时保护，建议在机器人控制节点实现看门狗

**推荐方案：** 参见"高级安全建议"章节的"看门狗（Watchdog）机制"

---

## 通信流程图

```
┌─────────────────┐
│  物理手柄设备    │  (8BitDo 蓝牙/USB)
│  (硬件层)       │
└────────┬────────┘
         │
         │ USB/蓝牙信号
         ▼
┌─────────────────┐
│ Linux evdev 驱动│  (内核层)
│  /dev/input/    │
└────────┬────────┘
         │
         │ 原始事件 (EV_KEY, EV_ABS)
         ▼
┌─────────────────────────────┐
│   joystick_node             │
│   (ROS2 驱动节点)            │
│                             │
│  1. 读取原始事件             │
│  2. 映射按键/摇杆            │
│  3. 归一化数值 (-1.0~1.0)   │
│  4. 应用死区过滤             │
│  5. 打包成 Joystick 消息     │
└────────┬────────────────────┘
         │
         │ 发布到话题
         ▼
┌─────────────────┐
│  /joystick_data │  (ROS2 Topic)
│   (消息总线)     │
└────────┬────────┘
         │
         │ 订阅
         ▼
┌─────────────────────────┐
│  机器人控制节点          │  (你的程序)
│  - 电机控制              │
│  - 云台控制              │
│  - 武器系统等...         │
└─────────────────────────┘
```

---

## 🔖 ROS2 接口参考

### 节点（Nodes）

| 节点名 | 包名 | 可执行文件 | 描述 |
|--------|------|-----------|------|
| `joystick_node` | `my_joystick_driver` | `joystick_node` | 手柄驱动主节点 |

**启动命令：**
```bash
ros2 run my_joystick_driver joystick_node
```

---

### 话题（Topics）

| 话题名 | 消息类型 | 方向 | 频率 | 描述 |
|--------|---------|------|------|------|
| `/joystick_data` | `my_joystick_msgs/msg/Joystick` | 发布 | 20Hz | 手柄的实时状态数据 |

**查看话题：**
```bash
# 列出所有话题
ros2 topic list

# 查看话题详情
ros2 topic info /joystick_data

# 实时查看数据
ros2 topic echo /joystick_data

# 查看发布频率
ros2 topic hz /joystick_data
```

---

### 参数（Parameters）

| 参数名 | 类型 | 默认值 | 描述 |
|--------|------|--------|------|
| `auto_detect` | bool | `true` | 是否自动检测手柄设备 |
| `device_path` | string | `""` | 手动指定设备路径（需 `auto_detect=false`） |
| `device_name_filter` | string | `"8BitDo"` | 自动检测时的设备名称过滤器 |

**参数使用：**
```bash
# 查看所有参数
ros2 param list /joystick_node

# 查看单个参数值
ros2 param get /joystick_node auto_detect

# 启动时设置参数
ros2 run my_joystick_driver joystick_node --ros-args \
  -p auto_detect:=false \
  -p device_path:="/dev/input/event5"
```

---

### 消息格式（Message）

**消息类型：** `my_joystick_msgs/msg/Joystick`

**字段定义：**
```
# 模拟轴（整数，-8192 到 8192）
int32 lx      # 左摇杆 X 轴
int32 ly      # 左摇杆 Y 轴
int32 rx      # 右摇杆 X 轴
int32 ry      # 右摇杆 Y 轴
int32 dx      # 方向键 X 轴（-8192, 0, 8192）
int32 dy      # 方向键 Y 轴（-8192, 0, 8192）
int32 l2      # 左扳机（0 到 8192）
int32 r2      # 右扳机（0 到 8192）

# 数字按键（布尔值）
bool a        # A 键
bool b        # B 键
bool x        # X 键
bool y        # Y 键
bool l1       # 左肩键
bool r1       # 右肩键
bool l3       # 左摇杆按下
bool r3       # 右摇杆按下
bool select   # 选择键
bool start    # 开始键
```

**查看消息定义：**
```bash
ros2 interface show my_joystick_msgs/msg/Joystick
```

---

## 使用方法

### 0. 连接手柄到系统

在启动驱动之前，需要先将手柄连接到树莓派/Linux 系统。

#### 方式 A：蓝牙连接（推荐）

**步骤 1：进入蓝牙配对模式**
```bash
bluetoothctl
```

**步骤 2：打开蓝牙并扫描**
```bash
power on
scan on
```

**步骤 3：让手柄进入配对模式**
- 8BitDo 手柄：长按 **SELECT + START** 约 3 秒，LED 闪烁
- Xbox 手柄：按配对按钮
- PS 手柄：按 **Share + PS** 按钮

你会看到：
```
[NEW] Device XX:XX:XX:XX:XX:XX 8BitDo Pro 2
```

**步骤 4：配对、信任并连接**
```bash
pair XX:XX:XX:XX:XX:XX    # 替换为你的 MAC 地址
trust XX:XX:XX:XX:XX:XX   # 下次开机自动连接
connect XX:XX:XX:XX:XX:XX
exit
```

**步骤 5：验证连接**
```bash
# 查看设备是否被系统识别
ls -l /dev/input/by-id/
# 或者
sudo evtest
```

应该能看到你的手柄设备（例如 `/dev/input/event5`）。

#### 方式 B：USB 连接

直接用 USB 线连接手柄和树莓派即可，无需配对。连接后验证：
```bash
ls -l /dev/input/event*
sudo evtest  # 选择你的手柄设备，按几个按键测试
```

#### 权限配置（首次使用必做）

```bash
# 将当前用户加入 input 组
sudo usermod -a -G input $USER

# 重启使权限生效
sudo reboot
```

### 1. 编译工作空间

```bash
cd /home/robotics/temp/new_ws
colcon build
```

### 2. 配置环境变量

**每次打开新终端时需要执行：**
```bash
source /home/robotics/temp/new_ws/install/setup.bash
```

**或者一劳永逸（自动加载）：**
```bash
echo "source /home/robotics/temp/new_ws/install/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

### 3. 启动驱动节点

#### 方式 1：自动检测模式（默认，推荐）

```bash
ros2 run my_joystick_driver joystick_node
```

**预期输出：**
```
[INFO] [joystick_node]: Joystick publisher node initialized
[INFO] [joystick_node]: Configuration: auto_detect=True, device_path='', filter='8BitDo'
[INFO] [joystick_node]: Joystick states reset to safety (all zeros)
[INFO] [joystick_node]: Auto-detected device: 8BitDo Pro 2
```

#### 方式 2：使用其他品牌手柄（如 Xbox）

```bash
ros2 run my_joystick_driver joystick_node --ros-args -p device_name_filter:="Xbox"
```

#### 方式 3：手动指定设备路径

```bash
ros2 run my_joystick_driver joystick_node --ros-args -p auto_detect:=false -p device_path:="/dev/input/event5"
```

**适用场景：**
- 有多个手柄，需要精确指定某一个
- 使用了 udev 规则创建固定符号链接
- 自动检测不稳定时的备用方案

#### 方式 4：使用启动文件（多参数配置）

创建 `my_joystick.launch.py`：
```python
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='my_joystick_driver',
            executable='joystick_node',
            name='joystick_node',
            parameters=[{
                'auto_detect': True,
                'device_name_filter': '8BitDo'
            }]
        )
    ])
```

启动：
```bash
ros2 launch my_joystick.launch.py
```

### 4. 查看实时数据

在另一个终端执行：
```bash
ros2 topic echo /joystick_data
```

**示例输出：**
```yaml
lx: 6144      # 左摇杆向右推 75%
ly: -4096     # 左摇杆向下推 50%
rx: 0
ry: 0
dx: 0
dy: 0
l2: 6553      # 左扳机按下 80%
r2: 0
a: true       # A 键按下
b: false
x: false
y: false
l1: false
r1: false
l3: false
r3: false
select: false
start: false
```

### 5. 查看和修改参数（🆕 运行时配置）

**查看当前参数：**
```bash
ros2 param list /joystick_node
```

**输出：**
```
auto_detect
device_name_filter
device_path
use_sim_time
```

**查看参数值：**
```bash
ros2 param get /joystick_node auto_detect
ros2 param get /joystick_node device_name_filter
```

**动态修改参数（不推荐，建议重启节点）：**
```bash
ros2 param set /joystick_node device_name_filter "Xbox"
```

### 6. 检查话题信息

```bash
# 查看话题列表
ros2 topic list

# 查看话题频率
ros2 topic hz /joystick_data

# 查看消息类型
ros2 topic info /joystick_data
```

---

## 🆕 升级说明（v2.0）

### 新增功能

#### 1. ROS2 参数化配置 ⭐⭐⭐
**改进点：** 从硬编码配置升级为灵活的 ROS2 参数系统

**为什么更好？**
- ✅ 无需修改代码就能切换设备
- ✅ 支持多种手柄品牌（8BitDo, Xbox, PS5 等）
- ✅ 可以通过启动文件统一管理配置
- ✅ 符合 ROS2 最佳实践

**如何使用？**
```bash
# 旧版：只能用 8BitDo，要换手柄需要改代码
# 新版：一条命令搞定
ros2 run my_joystick_driver joystick_node --ros-args -p device_name_filter:="Xbox"
```

#### 2. 详细的设备调试信息 ⭐⭐
**改进点：** 连接失败时自动打印所有可用设备

**为什么更好？**
- ✅ 快速定位问题（是权限问题还是设备未识别）
- ✅ 获取正确的设备路径，无需手动 `ls /dev/input/`
- ✅ 显示设备的物理连接信息（USB 端口等）

**输出示例：**
```
=== Available Input Devices ===
  Path: /dev/input/event5
  Name: 8BitDo Pro 2
  Phys: usb-0000:00:14.0-3/input0
  ---
===============================
```

#### 3. 自动检测 + 手动指定双模式 ⭐⭐⭐
**改进点：** 支持自动扫描和手动指定两种模式

**为什么更好？**
- ✅ 开发测试：用自动模式，插上就能用
- ✅ 生产环境：用手动模式，精确控制每个设备
- ✅ 多手柄系统：可以分别指定不同的手柄

**如何使用？**
```bash
# 模式 1：自动（默认）
ros2 run my_joystick_driver joystick_node

# 模式 2：手动
ros2 run my_joystick_driver joystick_node --ros-args \
  -p auto_detect:=false \
  -p device_path:="/dev/input/event5"
```

### 对比旧版（Robocon2026_r2）

| 特性 | 旧版 | 新版 v2.0 | 提升 |
|------|------|-----------|------|
| **设备配置** | 固定路径 | 参数化 | 🔥🔥🔥 |
| **设备查找** | 硬编码 "8BitDo" | 可配置过滤器 | 🔥🔥 |
| **调试信息** | 基本提示 | 详细设备列表 | 🔥🔥 |
| **数据格式** | int32 原始值 | int32 归一化 (±8192) | 🔥🔥🔥 |
| **摇杆漂移** | 无处理 | 410 单位死区过滤 | 🔥🔥🔥 |
| **安全保护** | 无归零 | 断线自动归零 | 🔥🔥🔥 |
| **多手柄支持** | ❌ | ✅ | 🔥🔥 |
| **精度损失** | 无（保留原始） | 无（整数归一化） | 🔥🔥 |

---

## 故障排除

### 问题 1：找不到手柄设备
```
[WARN] [joystick_node]: No device found with filter '8BitDo'. Retrying...
=== Available Input Devices ===
  Path: /dev/input/event0
  Name: Logitech USB Receiver
  ...
```

**解决方法：**
1. 确认手柄已开机并配对
2. 检查设备列表中是否有你的手柄
3. 如果设备名不包含 "8BitDo"，使用自定义过滤器：
   ```bash
   ros2 run my_joystick_driver joystick_node --ros-args -p device_name_filter:="你的手柄名称"
   ```
4. 或者直接指定设备路径：
   ```bash
   ros2 run my_joystick_driver joystick_node --ros-args -p auto_detect:=false -p device_path:="/dev/input/event5"
   ```

### 问题 2：Permission denied
```
[ERROR] [joystick_node]: Permission denied. Add your user to 'input' group.
```

**解决方法：**
```bash
sudo usermod -a -G input $USER
sudo reboot  # 或者重新登录
```

### 问题 3：摇杆回中后有微小数值
这是正常现象（摇杆漂移）。代码已实现 410 单位（约 5%）死区过滤，如果仍然出现，可调整：
```python
# 在 joystick_node.py 第 42 行
self.deadzone = 820  # 增大到约 10%
```

### 问题 4：找到多个匹配的设备
如果有多个 8BitDo 手柄，系统会连接第一个找到的。建议使用手动模式：
```bash
# 先查看所有设备
ros2 run my_joystick_driver joystick_node  # 查看调试输出

# 然后指定具体路径
ros2 run my_joystick_driver joystick_node --ros-args -p auto_detect:=false -p device_path:="/dev/input/event7"
```

### 问题 5：手柄无法连接（蓝牙）

**症状：** `bluetoothctl` 中无法看到手柄

**解决步骤：**
```bash
# 1. 确认蓝牙服务运行
sudo systemctl status bluetooth

# 2. 重启蓝牙服务
sudo systemctl restart bluetooth

# 3. 重新进入配对模式
bluetoothctl
power on
scan on
# 让手柄进入配对模式（长按配对键）

# 4. 如果仍然失败，清除旧配对记录
remove XX:XX:XX:XX:XX:XX
# 然后重新配对
```

### 问题 6：驱动找不到设备，但 evtest 能看到

**症状：** 
```
[WARN] No device found with filter '8BitDo'
=== Available Input Devices ===
  Path: /dev/input/event5
  Name: 8Bitdo Lite 2    ← 注意名称大小写不同
```

**原因：** 设备名称过滤器不匹配（大小写敏感）

**解决方法：**
```bash
# 方法 1：使用名称的一部分
ros2 run my_joystick_driver joystick_node --ros-args -p device_name_filter:="Lite"

# 方法 2：直接指定路径
ros2 run my_joystick_driver joystick_node --ros-args \
  -p auto_detect:=false \
  -p device_path:="/dev/input/event5"
```

### 问题 7：如何测试手柄是否正常工作？

```bash
# 使用 evtest 工具测试
sudo apt install evtest
sudo evtest

# 选择你的手柄设备（例如输入 5）
# 按动摇杆和按键，应该能看到实时事件输出
```

---

## 🔧 完整诊断流程

如果遇到连接问题，按以下顺序排查：

### 1. 硬件层检查
```bash
# 检查手柄是否被系统识别
ls -l /dev/input/event*
ls -l /dev/input/by-id/

# 使用 evtest 测试原始输入
sudo evtest
```

### 2. 权限检查
```bash
# 检查当前用户组
groups
# 应该包含 "input"

# 如果没有，添加并重启
sudo usermod -a -G input $USER
sudo reboot
```

### 3. 启动驱动查看日志
```bash
source /home/robotics/temp/new_ws/install/setup.bash
ros2 run my_joystick_driver joystick_node
```

观察输出的设备列表，确认：
- 手柄是否出现在列表中
- 设备名称是否与过滤器匹配
- 设备路径是哪个（例如 `/dev/input/event5`）

### 4. 根据情况选择模式
```bash
# 情况 A：设备名称匹配 "8BitDo"
ros2 run my_joystick_driver joystick_node  # 默认即可

# 情况 B：设备名称不同（如 Xbox）
ros2 run my_joystick_driver joystick_node --ros-args -p device_name_filter:="Xbox"

# 情况 C：自动检测不稳定
ros2 run my_joystick_driver joystick_node --ros-args \
  -p auto_detect:=false \
  -p device_path:="/dev/input/event5"
```

### 5. 验证数据流
```bash
# 查看话题
ros2 topic list

# 查看实时数据
ros2 topic echo /joystick_data

# 推动摇杆，应该能看到数值变化（-8192 ~ 8192）
```

---

## 高级安全建议

### 当前已实现的安全特性
- ✅ 手柄断开时自动归零
- ✅ 节点关闭时安全停机
- ✅ 死区过滤防止漂移
- ✅ 自动重连机制
- ✅ 🆕 参数化配置，支持多种设备
- ✅ 🆕 详细调试信息，快速定位问题

### 推荐的额外安全层（未实现）
为了防止驱动节点崩溃导致机器人失控，建议在**机器人控制节点**中实现：

#### 看门狗（Watchdog）机制
```python
# 伪代码示例
class SafeRobotController(Node):
    def __init__(self):
        self.last_msg_time = self.get_clock().now()
        self.watchdog_timer = self.create_timer(0.1, self.check_timeout)
    
    def joystick_callback(self, msg):
        self.last_msg_time = self.get_clock().now()
        # 处理运动逻辑...
    
    def check_timeout(self):
        time_diff = (self.get_clock().now() - self.last_msg_time).nanoseconds / 1e9
        if time_diff > 0.2:  # 超过 0.2 秒没收到数据
            self.emergency_stop()  # 强制急停
```

---

## 技术细节

### 为什么混用 Python 和 C++？
- **驱动节点**：100% Python（`joystick_node.py`）
- **消息包**：自动生成 C++ 和 Python 代码

**原因：**
1. **跨语言兼容**：未来如果需要用 C++ 写高性能控制器，可以直接订阅同一个话题
2. **底层性能**：ROS2 的 DDS 通信层是 C++ 实现的，消息序列化需要 C++ 库支持
3. **开发效率**：Python 适合快速开发驱动，C++ 适合性能关键的任务

### 死区算法原理
```python
def apply_deadzone(value, threshold=0.05):
    if abs(value) < threshold:
        return 0.0
    return value
```

### 归一化公式
```python
# 对称轴（摇杆）
normalized = (raw_value - center) / half_range

# 单向轴（扳机）
normalized = (raw_value - min) / (max - min)
```

---

## 参考资料

- [ROS2 官方文档](https://docs.ros.org/en/humble/)
- [evdev Python 库](https://python-evdev.readthedocs.io/)
- [Linux Input Subsystem](https://www.kernel.org/doc/html/latest/input/)

---

## 许可证

本项目仅供学习和研究使用。

---

## 作者

eduhk_robotics@hero
