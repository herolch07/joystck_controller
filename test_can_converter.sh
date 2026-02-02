#!/bin/bash
# CAN Bus Converter Test Script for HDSC CDC Device

echo "=========================================="
echo "🚗 CAN Bus Converter Test Script"
echo "=========================================="
echo ""

DEVICE="/dev/ttyACM0"
DEVICE_ID="usb-HDSC_CDC_Device_00000000050C-if00"

echo "1. Device Detection..."
echo "   Looking for: $DEVICE_ID"
if ls /dev/serial/by-id/ | grep -q "$DEVICE_ID"; then
    echo "   ✓ Device found: $(ls -l /dev/serial/by-id/ | grep "$DEVICE_ID")"
    ACTUAL_DEVICE=$(basename $(readlink /dev/serial/by-id/$DEVICE_ID))
    echo "   ✓ Mapped to: /dev/$ACTUAL_DEVICE"
else
    echo "   ✗ Device not found in /dev/serial/by-id/"
    echo "   Available serial devices:"
    ls /dev/serial/by-id/ 2>/dev/null || echo "   (None)"
    exit 1
fi
echo ""

echo "2. Permission Check..."
PERMISSIONS=$(stat -c "%a %U:%G" /dev/$ACTUAL_DEVICE 2>/dev/null)
if [ $? -eq 0 ]; then
    echo "   Device permissions: $PERMISSIONS"
    if groups | grep -q dialout; then
        echo "   ✓ User is in dialout group"
    else
        echo "   ✗ User NOT in dialout group - adding now..."
        sudo usermod -a -G dialout $USER
        echo "   Please logout and login again, or reboot the system"
        echo "   For immediate testing, we'll use sudo for this session"
    fi
else
    echo "   ✗ Cannot check device permissions"
    exit 1
fi
echo ""

echo "3. Basic Communication Test..."
# Temporarily change permissions for testing
sudo chmod 666 /dev/$ACTUAL_DEVICE 2>/dev/null

# Test if we can open the device
if echo "test" > /dev/$ACTUAL_DEVICE 2>/dev/null; then
    echo "   ✓ Can write to device"
else
    echo "   ✗ Cannot write to device"
    echo "   Trying with sudo..."
    if sudo echo "test" > /dev/$ACTUAL_DEVICE 2>/dev/null; then
        echo "   ✓ Can write with sudo"
    else
        echo "   ✗ Cannot write even with sudo"
        exit 1
    fi
fi

# Try to read some response (timeout after 2 seconds)
echo "   Testing device response..."
timeout 2 cat /dev/$ACTUAL_DEVICE > /tmp/can_test_output 2>/dev/null &
CAT_PID=$!
sleep 1

# Send a simple command (this might trigger some response)
echo -ne "\x01\x02\x03\x04" > /dev/$ACTUAL_DEVICE 2>/dev/null

sleep 1
kill $CAT_PID 2>/dev/null

if [ -s /tmp/can_test_output ]; then
    echo "   ✓ Received response from device"
    echo "   Response data (hex):"
    hexdump -C /tmp/can_test_output | head -5
else
    echo "   ? No response received (may be normal for this device type)"
fi
rm -f /tmp/can_test_output
echo ""

echo "4. Motor Controller Test..."
echo "   Testing with actual motor controller node..."

# Source ROS2 environment
if [ -f "/home/robotics/robocon/new_ws/install/setup.bash" ]; then
    source /home/robotics/robocon/new_ws/install/setup.bash
    echo "   ✓ ROS2 workspace sourced"
else
    echo "   ✗ ROS2 workspace not found"
    echo "   Please compile the workspace first: colcon build"
    exit 1
fi

# Check if the motor controller package exists
if ros2 pkg list | grep -q base_omniwheel_r2_700; then
    echo "   ✓ Motor controller package found"
else
    echo "   ✗ Motor controller package not found"
    exit 1
fi

echo ""
echo "=========================================="
echo "🔧 Manual Testing Instructions"
echo "=========================================="
echo ""
echo "To test the complete hand controller system:"
echo ""
echo "Terminal 1 - Start hand controller:"
echo "  ./launch_hand_controller.sh"
echo ""
echo "Terminal 2 - Monitor motor commands:"
echo "  ros2 topic echo /damiao_control"
echo ""
echo "Terminal 3 - Test manual movement:"
echo "  ros2 topic pub /local_driving std_msgs/msg/Float32MultiArray '{data: [0.0, 50.0, 0.0]}' --once"
echo ""
echo "Expected behavior:"
echo "  - You should see motor commands in Terminal 2"
echo "  - Motors should respond to joystick input"
echo "  - Robot should move according to controller commands"
echo ""
echo "Troubleshooting:"
echo "  - Check motor power is ON"
echo "  - Verify CAN bus wiring is correct"
echo "  - Ensure all 4 motors are connected"
echo "  - Run diagnose_damiao.sh for detailed diagnostics"
echo ""