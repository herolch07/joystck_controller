#!/bin/bash
# Sudo-based Hand Controller Launch Script

echo "=========================================="
echo "🎮 Sudo-based Hand Controller Launch"
echo "=========================================="
echo ""

# 检查是否以 sudo 运行
if [ "$EUID" -ne 0 ]; then
    echo "This script needs to run with sudo privileges"
    echo "Please run: sudo $0"
    exit 1
fi

# 切换到正确的工作目录
cd /home/robotics/robocon/new_ws

# 设置环境变量
export PYTHONPATH="/home/robotics/robocon/new_ws/install/my_joystick_driver/lib/python3.12/site-packages:/home/robotics/robocon/new_ws/install/my_joystick_msgs/lib/python3.12/site-packages:/opt/ros/jazzy/lib/python3.12/site-packages"
export HOME="/home/robotics"

echo "Starting hand controller system..."
echo ""

# 启动各个节点
echo "1. Starting joystick driver..."
sudo -u robotics /home/robotics/robocon/new_ws/install/my_joystick_driver/lib/my_joystick_driver/joystick_node &
JOY_PID=$!
sleep 2

echo "2. Starting joystick bridge..."
sudo -u robotics /home/robotics/robocon/new_ws/install/joystick_bridge/bin/joystick_bridge &
BRIDGE_PID=$!
sleep 2

echo "3. Starting motor controller..."
sudo -u robotics /home/robotics/robocon/new_ws/install/base_omniwheel_r2_700/lib/base_omniwheel_r2_700/damiao_node &
MOTOR_PID=$!
sleep 3

echo "4. Starting navigation controller..."
sudo -u robotics /home/robotics/robocon/new_ws/install/base_omniwheel_r2_700/lib/base_omniwheel_r2_700/local_navigation_node &
NAV_PID=$!
sleep 2

echo ""
echo "✅ All nodes started successfully!"
echo "Process IDs:"
echo "  Joystick Driver: $JOY_PID"
echo "  Joystick Bridge: $BRIDGE_PID"
echo "  Motor Controller: $MOTOR_PID" 
echo "  Navigation Controller: $NAV_PID"
echo ""
echo "🔌 Connect your hand controller now!"
echo "🕹️  Move the joysticks to control the robot"
echo ""
echo "To stop: Press Ctrl+C or run 'sudo pkill -f python3'"
echo ""

# 等待用户中断
wait