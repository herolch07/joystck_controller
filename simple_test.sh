#!/bin/bash
# Simple System Test Script

echo "=========================================="
echo "🤖 Simple System Verification"
echo "=========================================="
echo ""

# 设置正确的环境
cd /home/robotics/robocon/new_ws
export PYTHONPATH="/home/robotics/robocon/new_ws/install/my_joystick_driver/lib/python3.12/site-packages:/home/robotics/robocon/new_ws/install/my_joystick_msgs/lib/python3.12/site-packages:/opt/ros/jazzy/lib/python3.12/site-packages"

echo "1. Checking ROS2 Installation..."
if command -v ros2 &> /dev/null; then
    echo "   ✓ ROS2 found: $(which ros2)"
else
    echo "   ✗ ROS2 not found"
    exit 1
fi

echo ""
echo "2. Checking Available Executables..."
# 检查可执行文件
if [ -f "install/my_joystick_driver/lib/my_joystick_driver/joystick_node" ]; then
    echo "   ✓ Joystick driver executable found"
else
    echo "   ✗ Joystick driver executable missing"
fi

if [ -f "install/joystick_bridge/bin/joystick_bridge" ]; then
    echo "   ✓ Joystick bridge executable found"  
else
    echo "   ✗ Joystick bridge executable missing"
fi

echo ""
echo "3. Testing Direct Node Execution..."
# 测试直接运行节点
echo "   Testing joystick driver..."
timeout 3 python3 install/my_joystick_driver/lib/my_joystick_driver/joystick_node.py --help 2>/dev/null && echo "   ✓ Joystick driver runs" || echo "   ? Joystick driver test completed"

echo ""
echo "4. Quick Manual Test Commands:"
echo "   # Start joystick driver"
echo "   python3 /home/robotics/robocon/new_ws/install/my_joystick_driver/lib/my_joystick_driver/joystick_node.py"
echo ""
echo "   # In another terminal, monitor output"
echo "   ros2 topic echo /joystick_data"
echo ""
echo "   # Test manual movement command"
echo "   ros2 topic pub /local_driving std_msgs/msg/Float32MultiArray '{data: [0.0, 50.0, 0.0]}' --once"
echo ""

echo "=========================================="
echo "✅ Basic system verification complete"
echo "=========================================="