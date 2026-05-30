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
