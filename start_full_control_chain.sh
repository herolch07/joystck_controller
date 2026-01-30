#!/bin/bash
# 启动完整的手柄控制链

echo "=== 启动手柄控制链 ==="

# Source ROS2 环境
source /home/robotics/temp/new_ws/install/setup.bash

echo "1/4 启动手柄驱动..."
gnome-terminal --tab --title="Joystick Driver" -- bash -c "
source /home/robotics/temp/new_ws/install/setup.bash
ros2 run my_joystick_driver joystick_node
exec bash
"

sleep 2

echo "2/4 启动转换节点..."
gnome-terminal --tab --title="Joystick Bridge" -- bash -c "
source /home/robotics/temp/new_ws/install/setup.bash
ros2 run joystick_bridge joystick_bridge
exec bash
"

sleep 2

echo "3/4 启动底盘驱动..."
gnome-terminal --tab --title="Damiao Node" -- bash -c "
cd /home/robotics/temp/Robocon2026_r2/2026R2_ws
source install/setup.bash
ros2 run base_omniwheel_r2_700 damiao_node
exec bash
"

sleep 2

echo "4/4 启动导航节点..."
gnome-terminal --tab --title="Navigation Node" -- bash -c "
cd /home/robotics/temp/Robocon2026_r2/2026R2_ws
source install/setup.bash
ros2 run base_omniwheel_r2_700 local_navigation_node
exec bash
"

echo ""
echo "✅ 所有节点已启动！"
echo "使用说明："
echo "- 左摇杆：控制移动方向和速度"
echo "- 右摇杆左右：控制旋转"
echo "- 摇杆回中：停止"
echo ""
echo "调试命令："
echo "ros2 topic echo /local_driving"
echo "ros2 topic echo /damiao_control"