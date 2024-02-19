from setuptools import find_packages
from setuptools import setup

setup(
    name='velodyne_control_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('velodyne_control_msgs', 'velodyne_control_msgs.*')),
)
