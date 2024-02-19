import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node

from moveit_configs_utils import MoveItConfigsBuilder

#def declare_args(context, *args, **kwargs):

def launch_setup(context, *args, **kwargs):
    robot_description_path = os.path.join(
    get_package_share_directory('tiago_description'), 'robots', 'tiago.urdf.xacro')
    
    robot_description_semantic = ('config/srdf/tiago_pal-gripper.srdf')
    
    moveit_simple_controllers_path = (
    'config/controllers/controllers_pal-gripper.yaml')

    moveit_config = (
    MoveItConfigsBuilder('tiago')
    .robot_description(file_path=robot_description_path)
    .robot_description_semantic(file_path=robot_description_semantic)
    .robot_description_kinematics(file_path=os.path.join('config', 'kinematics_kdl.yaml'))
    .trajectory_execution(moveit_simple_controllers_path)
    .planning_pipelines(pipelines=['ompl'])
    .pilz_cartesian_limits(file_path=os.path.join('config', 'pilz_cartesian_limits.yaml'))
    .to_moveit_configs()
    )

    use_sim_time = {
        'use_sim_time': LaunchConfiguration('use_sim_time')
    }

    # RViz
    #rviz_base = os.path.join(get_package_share_directory(
     #   'tiago_moveit_config'), 'config', 'rviz')
    #rviz_full_config = os.path.join(rviz_base, 'moveit.rviz')
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        output='log',
        #arguments=['-d', rviz_full_config],
        parameters=[
            use_sim_time,
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.planning_pipelines,
            moveit_config.robot_description_kinematics,
        ],
    )

    tiago_moveit_interface = Node(
        package='ros360_moveit',
        executable='tiago_moveit_interface',
        output='screen',
        parameters=[
            use_sim_time,
            moveit_config.robot_description,
            moveit_config.robot_description_semantic,
            moveit_config.planning_pipelines,
            moveit_config.robot_description_kinematics,
        ],
    )

    return [rviz_node, tiago_moveit_interface]

def generate_launch_description():

    sim_time_arg = DeclareLaunchArgument(
        'use_sim_time', default_value='True', description='Use sim time'
    )

    ld = LaunchDescription()

    # Declare arguments
    # we use OpaqueFunction so the callbacks have access to the context
    #ld.add_action(get_robot_name('tiago'))
    #ld.add_action(OpaqueFunction(function=declare_args))
    ld.add_action(sim_time_arg)

    # Execute move_group node
    ld.add_action(OpaqueFunction(function=launch_setup))

    return ld
