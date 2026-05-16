from setuptools import find_packages, setup


package_name = "keyboard_teleop"

setup(
    name=package_name,
    version="0.1.0",
    packages=find_packages(exclude=["test"]),
    data_files=[
        ("share/ament_index/resource_index/packages", ["resource/" + package_name]),
        ("share/" + package_name, ["package.xml"]),
    ],
    install_requires=["setuptools"],
    zip_safe=True,
    maintainer="EdUHK Robocon Team",
    maintainer_email="robotics@example.com",
    description="Keyboard operator teleoperation package",
    license="Apache License 2.0",
    entry_points={
        "console_scripts": [
            "keyboard_teleop_node = keyboard_teleop.keyboard_teleop_node:main",
        ],
    },
)
