import sys
if sys.prefix == '/home/robotics/.platformio/penv':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/robotics/temp/new_ws/install/joystick_bridge'
