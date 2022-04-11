import launch
from launch_ros.actions import ComposableNodeContainer
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
    """Generate launch description with multiple components."""
    container = ComposableNodeContainer(
            name='my_container',
            namespace='',
            package='rclcpp_components',
            executable='component_container',
            composable_node_descriptions=[
                ComposableNode(
                    package='rt2_assignment1',
                    plugin='rt2_assignment1::position_server',
                    name='random_position'),
                ComposableNode(
                    package='rt2_assignment1',
                    plugin='rt2_assignment1::state_machine',
                    name='state_machine')
            ],
            output='screen',
    )

    return launch.LaunchDescription([container])