from setuptools import find_packages
from setuptools import setup

setup(
    name='my_joystick_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('my_joystick_msgs', 'my_joystick_msgs.*')),
)
