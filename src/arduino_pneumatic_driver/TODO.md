# arduino_pneumatic_driver TODO

## 已完成

- [x] 新增 Arduino pneumatic driver package
- [x] 实现 `pneumatic_relay_driver_node`
- [x] 实现 `pneumatic_gripper_joystick_bridge_node`
- [x] 使用 Arduino 已测试协议 `[0,0]` / `[1,1]`
- [x] 默认使用稳定串口 `/dev/serial/by-id/usb-1a86_USB2.0-Serial-if00-port0`
- [x] 实现 timeout 后发送 safe state `[1,1]`
- [x] README 记录 topic、参数、timeout、安全状态和最小测试
- [x] 分离 D9 gripper open/close 与 D8 height high/low 控制
- [x] pneumatic joystick bridge 改为 20Hz 持续发布当前状态，避免 relay 闪烁
- [x] 回退持续发布方案，只保留 B 控制 gripper open，D8 保持 HIGH
- [x] 按新需求改为初始 height LOW，按 A 后 height HIGH 并保持
- [x] 增加 X 锁定 height LOW，直到再次按 A

## 待完成

- [ ] 增加 launch 文件和 YAML 参数文件
- [x] 旧 `[1,0]` 启动策略已被新接线废弃；当前 timeout/startup 使用 `[1,1]` = CLOSE + HIGH
- [ ] 增加 Arduino PING/PONG 心跳协议
- [ ] 增加无硬件 serial mock 测试
- [ ] 后续如 valve 数量增加，将 command message 升级为自定义 msg

## v7 新 relay 接线映射

- [x] v7 假设 `A` 控 arm gripper OPEN latch，后续 v9 实机确认已覆盖
- [x] v7 假设 `X` 控 arm gripper CLOSE latch，后续 v9 实机确认已覆盖
- [x] v7 假设 `B` 控 height，后续 v9 实机确认已覆盖
- [x] joystick timeout 后输出 `[1,1]`，避免 height LOW 被保持
- [x] 文档同步当前 A/X/B 控制语义

## v8 启动默认 height LOW

- [x] `initial_height_state` 改为 `0`
- [x] v8 standalone pneumatic driver `safe_state` 曾改为 `[1,0]`，v10 已按 relay 顺序修正为 `[0,1]`
- [x] joystick timeout 后回 `[1,0]`
- [x] v8 启动默认 LOW 逻辑保留；v9 后 B 不再控制 height

## v9 实机确认 B/A/X 映射

- [x] `B` 控 arm gripper：按住 OPEN，松开 CLOSE
- [x] `A` 控 arm height LOW
- [x] `X` 控 arm height HIGH
- [x] startup/timeout 保持 `[1,0]` = CLOSE + LOW

## v10 relay 顺序实机确认

- [x] `/pneumatic_gripper_cmd` 顺序改为 `[height_state, gripper_state]`
- [x] startup/timeout safe state 改为 `[0,1]`
- [x] `B` 只控制 gripper，`A/X` 只控制 height

## v11 arm height 单键切换

- [x] 将 `A=LOW`、`X=HIGH` 改为默认 `A` 单键切换 LOW/HIGH
- [x] 使用按钮上升沿切换，避免长按时按 joystick 发布频率反复翻转
- [x] 新增 `height_toggle_button` 参数，允许通过参数更换按钮
- [x] timeout 后回到 `[0,1]`，并要求切换按钮先松开再重新按下
- [x] 新增无硬件单键切换测试
- [x] README 追加 v11 当前映射与串口协议说明
- [ ] 实机确认每按一次 `A` 只切换一次高度，`X` 已释放

## v12 arm gripper 单键锁定与默认 OPEN

- [x] 将 `B` 从按住 OPEN 改为每次按下切换 OPEN/CLOSE
- [x] 使用 B 按钮上升沿，避免长按时重复切换
- [x] arm bridge 启动和 joystick timeout 默认改为 `[0,0]` = LOW + OPEN
- [x] timeout 后要求 A/B 先松开再重新按下
- [x] standalone pneumatic driver `safe_state` 改为 `[0,0]`
- [x] 新增 B 锁定切换与 timeout 恢复测试
- [x] README 追加 v12 当前行为和释放夹持物风险
- [ ] 实机确认启动默认 OPEN、B 每按一次只切换一次
- [ ] 实机确认 joystick timeout 后 arm gripper OPEN 符合机构安全要求


## v13 Motor7/8 双 arm 气动选择控制

- [x] bridge 订阅 `/motor_position_selector_status`
- [x] A/B 根据当前 Motor7/8 选择路由
- [x] SELECT 仅控制 Motor8 inclination
- [x] Motor7 与 Motor8 分别保存锁定状态
- [x] 五位 arm command 默认安全值改为 `[0,1,0,1,1]`
- [x] 保留 `input_timeout_sec=0.3 s` watchdog
- [x] 新增 selector 索引、安全状态和上升沿测试
- [ ] 实机确认 START 切换后 A/B 只改变所选 arm
- [ ] 实机确认 SELECT 只改变 Motor8 inclination
- [ ] 实机确认 joystick 断开后所有 arm 回到安全状态

## v14 七路 Arduino panel 相容性

- [x] 確認本 bridge 仍發布五路 `/pneumatic_gripper_cmd`
- [x] 確認七路 serial output 由 `kfs_staff_gripper_arduino_node` 合併處理
- [x] 保持 A/B/SELECT 與 Motor7/8 selector 邏輯不變
- [x] 記錄 Relay 7 / Pin 28 暫時不由本 package 控制
- [ ] Relay 7 用途確認後，再評估是否需要本 package 新增一個控制欄位

## v15 Motor7 inclination

- [x] 將 Relay 7 / Pin 28 記錄為 Motor7 inclination
- [x] `/pneumatic_gripper_cmd` 從五路擴為六路
- [x] `DEFAULT_ARM_SAFE_STATE` 改為 `[0,1,0,1,1,0]`
- [x] SELECT 改為控制目前選中 arm 的 inclination
- [x] 新增 selected inclination index 測試
- [ ] 實機確認 Motor7/Motor8 切換後 SELECT 只作用於選中 arm
