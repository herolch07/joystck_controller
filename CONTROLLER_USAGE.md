# R1 Controller Usage - Current Keymap

> Last updated: 2026-06-19
> 本文件是目前手柄操作的唯一準則。其他 README 中較早日期的鍵位章節保留為歷史紀錄；實機操作以本文件為準。

## 1. Operation Mode

手柄中間兩個鍵只負責切換模式，不直接移動 motor，也不直接切 relay。

| 按鍵 | 模式 | `/operation_mode` |
|---|---|---|
| SELECT / 中左 | STAFF mode | `1` |
| START / 中右 | KFS mode | `2` |
| 手柄超時 | INVALID | `0` |

比賽 zone 用法：

```text
Zone 1: 機手切到 STAFF mode
Zone 2: 機手切到 KFS mode
Zone 3: 機手自行在 STAFF / KFS mode 之間切換
```

## 2. Always Active Controls

以下控制不受 STAFF/KFS mode 影響：

| 控制 | 功能 |
|---|---|
| Left stick | 底盤平移，人視角控制 |
| Right stick | 底盤旋轉 |
| D-pad | 設定 KFS visual front 在人視角中的方向 |
| X + Y + B + A 長按 5 秒 | Raspberry Pi shutdown command |

D-pad 語義：

| D-pad | 意義 |
|---|---|
| Up | KFS visual front 在機手前方 |
| Right | KFS visual front 在機手右方 |
| Down | KFS visual front 在機手後方 / 靠近機手 |
| Left | KFS visual front 在機手左方 |

目前實機校正後的換算：

```text
body_front_view = (KFS view - 1) % 4
```

開機預設等同 D-pad Up，也就是 `view=0`，假設 KFS visual front 在機手前方。

## 3. STAFF Mode Current Keymap

進入 STAFF mode：

```text
按 SELECT / 中左
/operation_mode = 1
```

| 控制 | 功能 | ROS output |
|---|---|---|
| A | Motor7 左右 90° / preset cycle only | `/motor7_position_input` toggle |
| X | Motor8 左右 90° / preset cycle only | `/motor8_position_input` toggle |
| B | Motor7 staff gripper relay toggle only | `/pneumatic_gripper_cmd[0]` |
| Y | Motor8 staff gripper relay toggle only | `/pneumatic_gripper_cmd[2]` |
| R1 | Motor7 manual trim negative | `/motor7_position_input[1] < 0` |
| R2 | Motor7 manual trim positive | `/motor7_position_input[1] > 0` |
| L1 | Motor8 manual trim negative | `/motor8_position_input[1] < 0` |
| L2 | Motor8 manual trim positive | `/motor8_position_input[1] > 0` |
| R3 / P1 | Motor7 head / inclination relay toggle | `/pneumatic_gripper_cmd[3]` |
| L3 / P2 | Motor8 head / inclination relay toggle | `/pneumatic_gripper_cmd[1]` |

注意：

```text
A/X 只控制位置模式 preset / 90° cycle，不再切 gripper relay。
B/Y 只控制 staff gripper relay，不再送 position preset。
R3/L3 來自手柄背鍵 remap：P1=R3，P2=L3。
```

STAFF pneumatic topic 順序：

```text
/pneumatic_gripper_cmd = [M7 gripper, M8 inclination, M8 gripper, M7 inclination]
safe_state = [1,0,1,0]
```

## 4. KFS Mode Current Keymap

進入 KFS mode：

```text
按 START / 中右
/operation_mode = 2
```

| 控制 | 功能 | ROS output |
|---|---|---|
| Y | KFS gripper open/close toggle | `/kfs_staff_gripper_cmd` |
| L2 | Motor6 horizontal positive / out | `/horizontal_speed_cmd > 0` |
| R2 | Motor6 horizontal negative / in | `/horizontal_speed_cmd < 0` |
| L1 | Motor5 elevator negative / down | `/elevator_speed_cmd < 0` |
| R1 | Motor5 elevator positive / up | `/elevator_speed_cmd > 0` |

KFS mode 不使用 A/B/X、L3/R3 來控制機構；左搖桿、右搖桿、D-pad 仍照常控制底盤視角。

## 5. Arduino Five-Relay Order

最新 Arduino sketch 使用 5 路 relay：

```text
relayPins = {22, 24, 25, 27, 28}
serial format = [r1,r2,r3,r4,r5]
HIGH = ON, LOW = OFF
```

ROS serial order：

```text
[KFS gripper, M7 gripper, M8 inclination, M8 gripper, M7 inclination]
```

全系統安全狀態：

```text
[0,1,0,1,0]
```

Topic 聚合：

```text
/kfs_staff_gripper_cmd -> serial[0]
/pneumatic_gripper_cmd -> serial[1:5]
```

## 6. Runtime Node Graph

```mermaid
graph LR
    Joy[/joystick_data/]
    Mode[operation_mode_selector_node<br/>SELECT=STAFF / START=KFS]
    ModeTopic[/operation_mode<br/>0 invalid / 1 STAFF / 2 KFS/]

    Base[joystick_bridge<br/>left stick / right stick / D-pad KFS view]
    Drive[/local_driving/]

    Pos[motor_position_selector_joystick_bridge_node<br/>STAFF: A/X/R1/R2/L1/L2]
    M7In[/motor7_position_input<br/>A + R1/R2/]
    M8In[/motor8_position_input<br/>X + L1/L2/]

    Pneu[pneumatic_gripper_joystick_bridge_node<br/>STAFF: B/Y/R3/L3]
    PneuCmd[/pneumatic_gripper_cmd<br/>M7 grip / M8 head / M8 grip / M7 head/]

    Kfs[kfs_staff_gripper_joystick_bridge_node<br/>KFS: Y]
    KfsCmd[/kfs_staff_gripper_cmd/]

    Horiz[horizontal_joystick_bridge_node<br/>KFS: L2/R2]
    HorizCmd[/horizontal_speed_cmd/]

    Elev[elevator_joystick_bridge_node<br/>KFS: L1/R1]
    ElevCmd[/elevator_speed_cmd/]

    Arduino[kfs_staff_gripper_arduino_node<br/>serial five-relay aggregator]

    Joy --> Mode --> ModeTopic
    Joy --> Base --> Drive
    Joy --> Pos
    ModeTopic --> Pos
    Pos --> M7In
    Pos --> M8In

    Joy --> Pneu
    ModeTopic --> Pneu
    Pneu --> PneuCmd --> Arduino

    Joy --> Kfs
    ModeTopic --> Kfs
    Kfs --> KfsCmd --> Arduino

    Joy --> Horiz
    ModeTopic --> Horiz
    Horiz --> HorizCmd

    Joy --> Elev
    ModeTopic --> Elev
    Elev --> ElevCmd
```

## 7. Quick Test

啟動系統後開多個 terminal 觀察：

```bash
ros2 topic echo /operation_mode
ros2 topic echo /motor7_position_input
ros2 topic echo /motor8_position_input
ros2 topic echo /pneumatic_gripper_cmd
ros2 topic echo /kfs_staff_gripper_cmd
ros2 topic echo /horizontal_speed_cmd
ros2 topic echo /elevator_speed_cmd
```

STAFF mode 預期：

```text
SELECT -> /operation_mode = 1
A      -> /motor7_position_input toggle
X      -> /motor8_position_input toggle
B      -> /pneumatic_gripper_cmd[0] toggle
Y      -> /pneumatic_gripper_cmd[2] toggle
R1/R2  -> /motor7_position_input trim negative/positive
L1/L2  -> /motor8_position_input trim negative/positive
R3/P1  -> /pneumatic_gripper_cmd[3] toggle
L3/P2  -> /pneumatic_gripper_cmd[1] toggle
```

KFS mode 預期：

```text
START -> /operation_mode = 2
Y     -> /kfs_staff_gripper_cmd toggle
L2/R2 -> /horizontal_speed_cmd positive/negative
L1/R1 -> /elevator_speed_cmd negative/positive
```
