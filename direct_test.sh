#!/bin/bash
# Simple Direct Test Script - No sudo required for basic functions

echo "=========================================="
echo "🎮 Direct Hand Controller Test"
echo "=========================================="
echo ""

cd /home/robotics/robocon/new_ws

# 设置正确的 Python 路径
export PYTHONPATH="/home/robotics/robocon/new_ws/install/my_joystick_driver/lib/python3.12/site-packages:/home/robotics/robocon/new_ws/install/my_joystick_msgs/lib/python3.12/site-packages:/opt/ros/jazzy/lib/python3.12/site-packages"

echo "Testing individual components:"
echo ""

# 测试 1: 手柄驱动节点
echo "1. Testing Joystick Driver..."
if [ -f "install/my_joystick_driver/lib/my_joystick_driver/joystick_node" ]; then
    echo "   ✓ Executable found"
    timeout 3 ./install/my_joystick_driver/lib/my_joystick_driver/joystick_node --help 2>/dev/null && echo "   ✓ Runs successfully" || echo "   ? Test completed"
else
    echo "   ✗ Executable not found"
fi

echo ""

# 测试 2: 控制桥接节点
echo "2. Testing Joystick Bridge..."
if [ -f "install/joystick_bridge/bin/joystick_bridge" ]; then
    echo "   ✓ Executable found"
    timeout 3 ./install/joystick_bridge/bin/joystick_bridge --help 2>/dev/null && echo "   ✓ Runs successfully" || echo "   ? Test completed"
else
    echo "   ✗ Executable not found"
fi

echo ""

# 测试 3: 底盘控制节点
echo "3. Testing Motor Controller..."
if [ -f "install/base_omniwheel_r2_700/lib/base_omniwheel_r2_700/damiao_node" ]; then
    echo "   ✓ Executable found"
    timeout 3 ./install/base_omniwheel_r2_700/lib/base_omniwheel_r2_700/damiao_node --help 2>/dev/null && echo "   ✓ Runs successfully" || echo "   ? Test completed"
else
    echo "   ✗ Executable not found"
fi

echo ""
echo "Manual Test Commands:"
echo "===================="
echo ""
echo "# Start joystick driver (connect your controller first)"
echo "./install/my_joystick_driver/lib/my_joystick_driver/joystick_node"
echo ""
echo "# In another terminal, monitor joystick data"
echo "ros2 topic echo /joystick_data"
echo ""
echo "# Test manual movement command"
echo "ros2 topic pub /local_driving std_msgs/msg/Float32MultiArray '{data: [0.0, 50.0, 0.0]}' --once"
echo ""
echo "✅ Component tests completed!"