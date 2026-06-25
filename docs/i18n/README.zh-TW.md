# EdUHK Robocon R1 ROS 2 Workspace

語言 / Language: [English](../../README.md) | [简体中文](README.zh-CN.md) | 繁體中文

本倉庫是 EdUHK Robocon Robotics Team 的 R1 機器人 ROS 2 控制工作區。當前最終版本以 8BitDo 手柄控制為主，涵蓋四輪全向底盤、達妙電機、STAFF gripper、KFS gripper、Arduino 五路繼電器氣動面板、自動啟動與多層安全 watchdog。

維護者：Hero@EdUHK Robotics Team 2026  
GitHub：`herolch07`

## 當前狀態

這是繁體中文 README。GitHub 首頁使用的英文主版在 [../../README.md](../../README.md)。

正式操作和接口說明以這些文件為準：

- [QUICK_START.md](../../QUICK_START.md)：最快啟動和驗證步驟
- [CONTROLLER_USAGE.md](../../CONTROLLER_USAGE.md)：當前手柄按鍵表
- [ARCHITECTURE.md](../../ARCHITECTURE.md)：系統架構和節點職責
- [NODE_GRAPH.md](../../NODE_GRAPH.md)：node/topic 數據流
- [TESTING_GUIDE.md](../../TESTING_GUIDE.md)：測試與實機檢查
- [SAFETY_REPORT.md](../../SAFETY_REPORT.md)：安全機制說明
- [arduino/five_relay_panel/five_relay_panel.ino](../../arduino/five_relay_panel/five_relay_panel.ino)：Arduino Mega 五路 relay 面板韌體

歷史文件和早期調參記錄只用於回溯，不再作為當前實機操作依據。清理前的舊版根目錄 README 已歸檔到 [../history/README.root-before-cleanup.md](../history/README.root-before-cleanup.md)。

## 命名說明

當前正確名稱是 **STAFF gripper**，不是 arm gripper。

倉庫中仍可能出現這些舊命名：

- `arm_gripper_controller_node`
- `arm_gripper_joystick_bridge_node`
- `/arm_gripper_speed_cmd`
- `/arm_gripper_status`

這些屬於舊的 Motor 7 速度控制鏈路，當前正式啟動腳本不再使用。當前 STAFF gripper 由以下鏈路控制：

- Motor 7 / Motor 8 位置控制：`motor7_position_controller_node`、`motor8_position_controller_node`
- STAFF pneumatic relay：`pneumatic_gripper_joystick_bridge_node`
- Arduino 五路 relay 聚合：`kfs_staff_gripper_arduino_node`

如果後續要真正重命名 package，建議將 `src/r1_arm_control` 改為 `src/r1_mechanism_control`，而不是 `staff_gripper_control`，因為它還負責 Motor 5 elevator 和 Motor 6 horizontal。

## 當前系統組成

```text
Motor 1-4  : 四輪全向底盤，VEL 模式
Motor 5    : KFS elevator，VEL 模式
Motor 6    : KFS horizontal，VEL 模式
Motor 7    : STAFF gripper position motor，POS_VEL 模式
Motor 8    : STAFF gripper position motor，POS_VEL 模式
Arduino    : 五路 relay 面板，控制 KFS gripper、Motor7/8 STAFF gripper relay、Motor7/8 head/inclination relay；韌體在 arduino/five_relay_panel/five_relay_panel.ino
Controller : 8BitDo 手柄，通過 Linux evdev 輸入
```

## 快速啟動

在機器人主機上：

```bash
cd /home/robotics/robocon2026_r1/r1_control_ws
colcon build --symlink-install
source install/setup.bash
chmod +x r1_start_base_1_0.sh
./r1_start_base_1_0.sh
```

啟動後會建立 tmux session：

```text
r1_control
```

常用 tmux 操作：

```text
進入窗口: tmux attach -t r1_control
離開窗口: Ctrl+b, then d
停止系統: tmux kill-session -t r1_control
```

## 當前啟動節點

`r1_start_base_1_0.sh` 是當前正式啟動腳本，會啟動：

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

不要把舊的 `start.sh`、`start_background.sh`、`start_ssh.sh` 當作當前正式入口。它們已歸檔到 `archive/legacy_scripts/`。

## 手柄按鍵

固定功能：

```text
左搖桿: 底盤平移，按操作者視角控制
右搖桿: 底盤原地旋轉
D-pad : 設置 KFS visual front 在操作者視角中的方向
X + Y + B + A 長按 5 秒: Raspberry Pi shutdown
```

模式選擇：

```text
SELECT / 中左: STAFF mode (/operation_mode = 1)
START  / 中右: KFS mode   (/operation_mode = 2)
```

STAFF mode：

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

KFS mode：

```text
Y     : KFS gripper toggle
L2/R2 : Motor6 horizontal positive(out) / negative(in)
L1/R1 : Motor5 elevator negative(down) / positive(up)
```

D-pad down 時，STAFF mode 會交換 Motor7/Motor8 的 STAFF gripper 控制映射，以適配操作者反向面對機器人時的操作直覺。詳細規則見 [CONTROLLER_USAGE.md](../../CONTROLLER_USAGE.md)。

## 當前重要參數

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

底盤當前標定：

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

## Package 地圖

```text
src/my_joystick_msgs          自定義 Joystick message
src/my_joystick_driver        evdev 手柄驅動，發布 /joystick_data
src/joystick_bridge           手柄到底盤 /local_driving 的橋接
src/base_omniwheel_r2_700     四輪全向底盤運動學與達妙電機驅動
src/operation_mode_control    STAFF/KFS 模式選擇
src/r1_arm_control            當前實際是 R1 mechanism control，含 Motor5/6/7/8 控制
src/arduino_pneumatic_driver  STAFF pneumatic bridge，發布 /pneumatic_gripper_cmd
src/kfs_staff_gripper         五路 Arduino relay 聚合與 KFS gripper bridge
arduino/five_relay_panel      Arduino Mega 五路 relay 韌體草圖
src/keyboard_teleop           鍵盤調試入口，非當前正式比賽入口
src/robot_power_control       手柄長按關機
```

## 安全機制

當前系統有多層 timeout/watchdog：

- `joystick_bridge`：`/joystick_data` 超時後發布 `/local_driving = [0,0,0]`。
- `local_navigation_node`：`/local_driving` 超時後向 Motor 1-4 發布零速度。
- `damiao_node`：電機命令超時後發零速度；反饋丟失或電機 disabled 後進入 recovery；恢復後必須收到 neutral command 才允許非零輸出。
- `r1_arm_control`：Motor5/6 速度控制超時歸零；Motor7/8 POS_VEL 輸入超時後停止 trim 並 hold 當前反饋位置。
- `operation_mode_control`：手柄輸入超時後發布 `MODE_INVALID`，下游 mechanism bridge 停止接受舊按鍵狀態。
- `kfs_staff_gripper_arduino_node`：Arduino 串口啟動、重連、關閉和命令源超時時寫入 safe state。
- `robot_power_control`：`X+Y+B+A` 長按觸發關機，默認節點支持 dry-run；正式啟動腳本當前傳入 `dry_run:=false`。

## 自動啟動

倉庫包含 systemd watcher：

```text
systemd/r1-control-autostart.service
scripts/wait_and_start_robot.sh
```

它會等待 8BitDo / Xbox 手柄出現後再啟動 `r1_start_base_1_0.sh`。當前 `STOP_ON_CONTROLLER_LOST=0`，手柄短暫斷連不會殺掉 tmux session，安全輸出由各節點 watchdog 負責。

## License

Copyright 2026 EdUHK Robotics Team(Architeacher)@Hero Lam.

本專案使用 Apache License 2.0。詳見 [LICENSE](../../LICENSE)。
