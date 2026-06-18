# robot_power_control TODO

## v0.1.0 joystick shutdown

- [x] 建立 `robot_power_control` package
- [x] 新增 `joystick_shutdown_node`
- [x] 預設 `X + Y + B + A` 長按 5 秒
- [x] 預設 `dry_run=true`，避免首次測試誤關機
- [x] 新增 `/robot_power_status`
- [x] 實作 joystick input timeout，超時清空長按計時
- [x] 新增無硬體單元測試
- [x] 新增 README.md
- [x] 新增 TODO.md
- [ ] 實機確認 dry-run 觸發
- [ ] 設定 sudoers 後確認 `dry_run=false` 真關機
- [ ] 根據實機手感決定是否調整 `hold_sec`
