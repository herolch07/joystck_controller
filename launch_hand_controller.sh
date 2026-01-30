#!/bin/bash
# Complete hand controller system launcher
# Starts all nodes needed for joystick-controlled base movement

echo "=========================================="
echo "🎮 ROBOCON Hand Controller System Launcher"
echo "=========================================="
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Source the workspace
source /home/robotics/robocon/new_ws/install/setup.bash

# Function to kill background processes on exit
cleanup() {
    echo -e "\n${YELLOW}Shutting down all nodes...${NC}"
    # Kill children first
    jobs -p | xargs -r kill 2>/dev/null
    # Wait for them to finish
    wait 2>/dev/null || true
    echo -e "${GREEN}All nodes stopped.${NC}"
}

# Set trap for cleanup
trap cleanup EXIT INT TERM

echo -e "${BLUE}Starting hand controller system...${NC}"
echo ""

# Start nodes in background
echo -e "${YELLOW}[1/4] Starting joystick driver...${NC}"
ros2 run my_joystick_driver joystick_node &
JOYSTICK_PID=$!
sleep 2

echo -e "${YELLOW}[2/4] Starting joystick bridge...${NC}"
ros2 run joystick_bridge joystick_bridge --ros-args -p max_speed_cm:=100.0 -p max_rotation:=2.0 &
BRIDGE_PID=$!
sleep 2

echo -e "${YELLOW}[3/4] Starting motor controller...${NC}"
ros2 run base_omniwheel_r2_700 damiao_node &
MOTOR_PID=$!
sleep 3

echo -e "${YELLOW}[4/4] Starting navigation controller...${NC}"
ros2 run base_omniwheel_r2_700 local_navigation_node &
NAV_PID=$!
sleep 2

# Check if all nodes started successfully
echo ""
echo -e "${BLUE}============================================${NC}"
echo -e "${BLUE}System Status${NC}"
echo -e "${BLUE}============================================${NC}"

if kill -0 $JOYSTICK_PID 2>/dev/null; then
    echo -e "${GREEN}✓ Joystick driver started (PID: $JOYSTICK_PID)${NC}"
else
    echo -e "${RED}✗ Failed to start joystick driver${NC}"
    exit 1
fi

if kill -0 $BRIDGE_PID 2>/dev/null; then
    echo -e "${GREEN}✓ Joystick bridge started (PID: $BRIDGE_PID)${NC}"
else
    echo -e "${RED}✗ Failed to start joystick bridge${NC}"
    exit 1
fi

if kill -0 $MOTOR_PID 2>/dev/null; then
    echo -e "${GREEN}✓ Motor controller started (PID: $MOTOR_PID)${NC}"
else
    echo -e "${RED}✗ Failed to start motor controller${NC}"
    exit 1
fi

if kill -0 $NAV_PID 2>/dev/null; then
    echo -e "${GREEN}✓ Navigation controller started (PID: $NAV_PID)${NC}"
else
    echo -e "${RED}✗ Failed to start navigation controller${NC}"
    exit 1
fi

echo ""
echo -e "${GREEN}🎉 All nodes started successfully!${NC}"
echo ""
echo -e "${BLUE}============================================${NC}"
echo -e "${BLUE}🎮 Hand Controller Ready${NC}"
echo -e "${BLUE}============================================${NC}"
echo ""
echo -e "${YELLOW}Connect your hand controller and start moving the robot!${NC}"
echo ""
echo "Control Mapping:"
echo "  Left Stick:  Move in X/Y directions"
echo "  Right Stick: Rotation control"
echo "  Press Ctrl+C to stop all nodes"
echo ""
echo "Debug Commands:"
echo "  View joystick data: ros2 topic echo /joystick_data"
echo "  View navigation commands: ros2 topic echo /local_driving"
echo "  View motor commands: ros2 topic echo /damiao_control"
echo ""
echo -e "${BLUE}============================================${NC}"

# Wait indefinitely
wait