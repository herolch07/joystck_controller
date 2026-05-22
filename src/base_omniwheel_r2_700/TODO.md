# base_omniwheel_r2_700 TODO

## 已完成

- [x] 实现 `local_navigation_node` 四轮全向底盘逆运动学
- [x] 实现 `damiao_node` 达妙电机 VEL 模式控制
- [x] 支持 Motor 1-7 初始化
- [x] 修复轮径换算，使用 `63.5 mm` 全向轮半径
- [x] 增加 `local_navigation_node` 输入 timeout，`/local_driving` 中断后 Motor 1-4 归零
- [x] 增加 `damiao_node` 电机级 watchdog，连续 VEL 命令超时后对应电机归零
- [x] README 追加 2026-05-14 安全更新说明
- [x] 修正 `local_navigation_node` 横向平移符号，避免左/右平移变成原地旋转
- [x] 将 `local_navigation_node` 的轮距、轮径、横向符号、旋转符号、电机方向改为 ROS 参数
- [x] 将 `local_navigation_node` 的 forward/lateral/rotation 运动基底改为可校准参数
- [x] 早期实机测试曾将 `lateral_axis_sign` 默认值校准为 `-1.0`；最终实机确认已在 2026-05-22 改为 `1.0`
- [x] 增加 `max_wheel_speed_rad_s` 轮速限幅，降低斜向/叠加动作导致驱动器过流风险
- [x] 增加 `max_wheel_accel_rad_s2` 加速度限制，降低摇杆突变导致 CAN/驱动器断连风险

## 待完成

- [ ] 将 `damiao_node` 拆分到独立 `damiao_driver` package，避免底盘 package 承担全机器人电机 driver 职责
- [ ] 将 `local_navigation_node` 参数整理到 YAML/launch 文件
- [ ] 将 `damiao_node` motor_id 映射改成 YAML/launch 参数
- [ ] 为 `local_navigation_node` 增加自动化测试
- [ ] 为 `damiao_node` 增加无硬件 mock 测试
- [ ] 整理旧 VESC 节点，确认是否仍属于当前 R1/R2 工程范围
- [ ] 实机重新校准斜向运动基底，确认右下、右上、左下、左上四个方向均无互相顶轮

## 2026-05-22 横向平移修复

- [x] 确认实机轮位为 Motor 1 左前、Motor 2 右前、Motor 3 右后、Motor 4 左后
- [x] 将 `local_navigation_node` 默认 `lateral_coeff_1..4` 修正为 `[1, -1, -1, 1]`
- [x] README 追加 v6 横向平移轮速基底修正说明
- [x] 实机测试左摇杆左推左横移、右推右横移
- [x] 根据实机反馈将 `lateral_axis_sign` 最终默认值记录为 `1.0`
- [ ] 重新测试斜向移动，确认前左/前右/后左/后右四个斜向无明显顶轮

## 2026-05-22 左右方向与右摇杆旋转修复

- [x] 根据实机反馈将 `lateral_axis_sign` 默认值改为 `1.0`
- [x] 将 `rotation_coeff_1..4` 改为 `[1, 1, 1, 1]`，使右摇杆使用原地旋转基底
- [x] README 追加 v7 左右方向与右摇杆原地旋转修正说明
- [x] 实机确认左摇杆左/右方向正确
- [x] 实机确认右摇杆左/右为原地旋转，可以正常工作
- [x] 实机确认当前 `rotation_axis_sign = 1.0` 可用，暂不需要反向

## 2026-05-22 最终实机确认

- [x] Controller 启动完整系统后，底盘前后、左右横移、原地旋转均工作成功
- [x] Motor 5 elevator 可由 L2/R2 控制
- [x] Motor 6 horizontal 可由 D-pad 左/右控制
- [x] Motor 7 arm gripper 可由 L1/R1 控制
- [x] Arduino pneumatic gripper 可由 A/B/X 控制
- [x] README 已追加 v8 最终实机确认版
- [ ] 后续将最终参数整理到 YAML/launch 文件，避免只依赖源码默认值
