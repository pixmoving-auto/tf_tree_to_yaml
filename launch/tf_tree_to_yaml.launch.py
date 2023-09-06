import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():

    parent_frame = DeclareLaunchArgument('parent_frame', default_value='sensor_top')
    child_frame = DeclareLaunchArgument('child_frame', default_value='[os_lidar_fl, os_lidar_fr]')
    output_yaml_file = DeclareLaunchArgument('output_yaml_file', default_value='tf_tree.yaml')
    
    node = Node(
        package='tf_tree_to_yaml',
        executable='tf_tree_to_yaml_node',
        name='tf_tree_to_yaml_node',
        parameters=[{
            'parent_frame': LaunchConfiguration("parent_frame"),
            'child_frame': LaunchConfiguration("child_frame"),
            'output_yaml_file': LaunchConfiguration("output_yaml_file"),
        }],
        output='screen')
        
    return LaunchDescription([
        parent_frame, 
        child_frame, 
        output_yaml_file, 
        node 
    ])
