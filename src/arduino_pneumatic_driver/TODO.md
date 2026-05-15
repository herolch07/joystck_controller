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

## 待完成

- [ ] 增加 launch 文件和 YAML 参数文件
- [ ] 根据真实 pneumatic 结构继续观察 `[1,1]` 作为 safe state 是否稳定
- [ ] 增加 Arduino PING/PONG 心跳协议
- [ ] 增加无硬件 serial mock 测试
- [ ] 后续如 valve 数量增加，将 command message 升级为自定义 msg
