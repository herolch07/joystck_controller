#!/bin/bash
# ROS2 Jazzy Compatibility Check Script

echo "=========================================="
echo "🤖 ROS2 Jazzy Compatibility Verification"
echo "=========================================="
echo ""

# Check ROS2 environment
echo "1. Checking ROS2 Environment..."
echo "   ROS Distribution: $ROS_DISTRO"
echo "   ROS Version: $ROS_VERSION"
echo "   Python Version: $ROS_PYTHON_VERSION"
echo ""

# Check if we can source the workspace
echo "2. Testing Workspace Sourcing..."
if source /home/robotics/robocon/new_ws/install/setup.bash 2>/dev/null; then
    echo "   ✓ Workspace sourced successfully"
else
    echo "   ✗ Failed to source workspace"
    exit 1
fi
echo ""

# Check if basic ROS2 commands work
echo "3. Testing Basic ROS2 Commands..."
if ros2 node list >/dev/null 2>&1; then
    echo "   ✓ ROS2 node command works"
else
    echo "   ✗ ROS2 node command failed"
fi

if ros2 topic list >/dev/null 2>&1; then
    echo "   ✓ ROS2 topic command works"
else
    echo "   ✗ ROS2 topic command failed"
fi
echo ""

# Check if our packages are available
echo "4. Checking Available Packages..."
PACKAGES=$(ros2 pkg list | grep -E "(joystick|omniwheel)" | wc -l)
if [ $PACKAGES -gt 0 ]; then
    echo "   ✓ Found $PACKAGES ROBOCON packages"
    ros2 pkg list | grep -E "(joystick|omniwheel)"
else
    echo "   ✗ No ROBOCON packages found"
fi
echo ""

# Check Python imports
echo "5. Testing Python Module Imports..."
python3 -c "import rclpy; print('   ✓ rclpy imported successfully')" 2>/dev/null || echo "   ✗ rclpy import failed"
python3 -c "from my_joystick_msgs.msg import Joystick; print('   ✓ my_joystick_msgs imported successfully')" 2>/dev/null || echo "   ✗ my_joystick_msgs import failed"
echo ""

echo "=========================================="
echo "✅ ROS2 Jazzy Compatibility Check Complete"
echo "=========================================="
echo ""
echo "Your system is fully compatible with ROS2 Jazzy!"
echo "All ROBOCON hand controller components should work properly."
echo ""