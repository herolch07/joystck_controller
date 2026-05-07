#!/usr/bin/env bash
set -e

WS_DIR="/home/robotics/robocon/new_ws"
SESSION="r1_base_control"

if ! command -v tmux >/dev/null 2>&1; then
    echo "tmux is not installed. Install it first:"
    echo "sudo apt install tmux"
    exit 1
fi

if tmux has-session -t "$SESSION" 2>/dev/null; then
    echo "tmux session '$SESSION' already exists."
    echo "Attach with:"
    echo "tmux attach -t $SESSION"
    echo ""
    read -r -p "Kill old session and restart? [y/N] " answer
    case "$answer" in
        y|Y|yes|YES)
            tmux kill-session -t "$SESSION"
            ;;
        *)
            exit 0
            ;;
    esac
fi

BASE_CMD="cd $WS_DIR && source install/setup.bash"

tmux new-session -d -s "$SESSION" -n "joystick" \
    "$BASE_CMD && ros2 run my_joystick_driver joystick_node; exec bash"

sleep 0.5

tmux new-window -t "$SESSION:1" -n "bridge" \
    "$BASE_CMD && python3 -m joystick_bridge.joystick_bridge; exec bash"

sleep 0.5

tmux new-window -t "$SESSION:2" -n "motors" \
    "$BASE_CMD && ros2 run base_omniwheel_r2_700 damiao_node; exec bash"

sleep 0.5

tmux new-window -t "$SESSION:3" -n "nav" \
    "$BASE_CMD && ros2 run base_omniwheel_r2_700 local_navigation_node; exec bash"

tmux new-window -t "$SESSION:4" -n "monitor" \
    "$BASE_CMD && echo 'Monitor commands:' && echo 'ros2 node list' && echo 'ros2 topic echo /joystick_data' && echo 'ros2 topic echo /local_driving' && echo 'ros2 topic echo /damiao_control' && echo 'ros2 param get /joystick_bridge max_speed_cm' && exec bash"

tmux select-window -t "$SESSION:4"

echo "Started R1 base control in tmux session '$SESSION'."
echo ""
echo "Attach:"
echo "tmux attach -t $SESSION"
echo ""
echo "Stop all:"
echo "tmux kill-session -t $SESSION"

tmux attach -t "$SESSION"
