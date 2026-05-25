# kfs_staff_gripper TODO

## v0.1.0 初始版本

- [x] 新增 `kfs_staff_gripper` ROS2 Python package
- [x] 新增 `kfs_staff_gripper_arduino_node`
- [x] 新增 `kfs_staff_gripper_joystick_bridge_node`
- [x] 支持 Arduino 四路 relay command `[r1,r2,r3,r4]`
- [x] 兼容现有 `/pneumatic_gripper_cmd`，统一管理同一个 Arduino serial port
- [x] 新增 `/kfs_staff_gripper_cmd` topic
- [x] 新增 `/kfs_staff_gripper_status` topic
- [x] 实现 arm pneumatic 与 KFS staff gripper 独立 command timeout，避免一个 topic 掩盖另一个 topic 的 watchdog
- [x] 实现 joystick timeout 后发布 staff safe_state
- [x] README 记录 topic、参数、启动方式、超时保护和 Arduino 注意事项
- [x] 更新 `r1_start_base_1_0.sh`，用四路 aggregator 替换旧 serial driver 并启动 KFS bridge

## 待实机确认

- [ ] 确认 KFS staff gripper relay 3/4 的真实高低电平触发方式
- [ ] 确认 staff relay 3/4 分别对应哪一个 pneumatic 动作
- [ ] 确认默认手柄映射 `Y/R3` 是否符合操作习惯
- [ ] 根据实机动作决定是否需要 latch 模式，而不是 hold-to-enable 模式
- [ ] 给 Arduino sketch 增加 millis watchdog，避免 USB 断线后 relay 保持最后状态

## 后续优化

- [ ] 如确认接线固定，增加 launch 文件统一启动 arm pneumatic bridge、KFS bridge 和 Arduino aggregator
- [ ] 根据比赛流程增加明确的 staff gripper safe_state 命名参数
- [ ] 增加 relay 状态到更结构化的 status topic
