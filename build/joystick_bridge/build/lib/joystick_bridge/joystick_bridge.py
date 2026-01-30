#!/usr/bin/env python3
"""
Joystick to Navigation Bridge Node

功能:
- 订阅手柄数据 (/joystick_data)
- 将摇杆映射到底盘运动指令
- 发布到 local_driving 话题

控制映射:
- 左摇杆 X (lx): 控制运动方向
- 左摇杆 Y (ly): 控制平移速度
- 右摇杆 X (rx): 控制旋转速度

符合 AGENTS.md 规范:
- 使用 Python 实现（规范 9.3）
- 包含完整注释和文档
- 参数化配置
- 明确的接口定义
"""

import rclpy
from rclpy.node import Node
from my_joystick_msgs.msg import Joystick
from std_msgs.msg import Float32MultiArray
import math

class JoystickBridge(Node):
    """
    手柄到底盘控制的桥接节点
    
    订阅: /joystick_data (my_joystick_msgs/Joystick)
        - lx, ly: 左摇杆坐标 (-8192 到 8192)
        - rx: 右摇杆 X 坐标 (-8192 到 8192)
    
    发布: /local_driving (std_msgs/Float32MultiArray)
        - [direction_rad, plane_speed_cm/s, rotation_rad/s]
    """
    
    def __init__(self):
        super().__init__('joystick_bridge')
        
        # 声明参数（符合 AGENTS.md 2.2.4 规范）
        self.declare_parameter('max_speed_cm', 100.0)
        self.declare_parameter('max_rotation', 2.0)
        self.declare_parameter('deadzone', 410)
        
        # 获取参数值
        self.max_speed_cm = self.get_parameter('max_speed_cm').get_parameter_value().double_value
        self.max_rotation = self.get_parameter('max_rotation').get_parameter_value().double_value
        self.deadzone = self.get_parameter('deadzone').get_parameter_value().integer_value
        
        # 订阅手柄数据
        self.joy_sub = self.create_subscription(
            Joystick,
            '/joystick_data',
            self.joystick_callback,
            10
        )
        
        # 发布底盘控制指令
        self.nav_pub = self.create_publisher(
            Float32MultiArray,
            '/local_driving',
            10
        )
        
        self.get_logger().info("Joystick bridge node initialized")
        self.get_logger().info(f"Max speed: {self.max_speed_cm} cm/s")
        self.get_logger().info(f"Max rotation: {self.max_rotation} rad/s")
        self.get_logger().info(f"Deadzone: {self.deadzone}")
    
    def joystick_callback(self, msg):
        """
        处理手柄输入并转换为底盘指令
        
        输入: Joystick 消息 (lx, ly, rx ∈ [-8192, 8192])
        输出: Float32MultiArray [direction_rad, speed_cm/s, rotation_rad/s]
        """
        # 从手柄读取数据
        lx = msg.lx  # 左摇杆 X
        ly = msg.ly  # 左摇杆 Y
        rx = msg.rx  # 右摇杆 X
        
        # 应用死区过滤
        if abs(lx) < self.deadzone:
            lx = 0
        if abs(ly) < self.deadzone:
            ly = 0
        if abs(rx) < self.deadzone:
            rx = 0
        
        # 转换为底盘指令
        if lx == 0 and ly == 0:
            # 摇杆回中：只考虑旋转
            direction = 0.0
            speed_cm = 0.0
        else:
            # 计算方向角 (弧度)
            # 注意：Y轴取反是因为手柄坐标系与机器人坐标系可能不同
            direction = math.atan2(float(lx), -float(ly))
            
            # 计算速度大小 (0-100%)
            magnitude = math.sqrt(lx*lx + ly*ly) / 8192.0
            speed_cm = magnitude * self.max_speed_cm
        
        # 计算旋转速度
        rotation = (rx / 8192.0) * self.max_rotation
        
        # 构造导航消息
        nav_msg = Float32MultiArray()
        nav_msg.data = [direction, speed_cm, rotation]
        
        # 发布指令
        self.nav_pub.publish(nav_msg)
        
        # 调试日志（只在有明显运动时输出）
        if speed_cm > 1.0 or abs(rotation) > 0.1:
            self.get_logger().debug(
                f"Joy: lx={lx}, ly={ly}, rx={rx} → "
                f"Nav: dir={math.degrees(direction):.1f}°, "
                f"speed={speed_cm:.1f}cm/s, rot={rotation:.2f}rad/s"
            )
    
    def destroy_node(self):
        """节点销毁时的安全处理"""
        # 发送停止指令
        stop_msg = Float32MultiArray()
        stop_msg.data = [0.0, 0.0, 0.0]
        self.nav_pub.publish(stop_msg)
        
        self.get_logger().info("Joystick bridge stopped - sent stop command")
        super().destroy_node()


def main(args=None):
    """主函数"""
    rclpy.init(args=args)
    node = JoystickBridge()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()