# Research Track 2 - First assignment - ROS2
##### Maria Luisa Aiachini - 4375373

## General behaviour
In this package you will find both [RIS1 package](https://github.com/Marilwoo/rt2_assignment1/tree/ros2) and [ROS2 package](https://github.com/Marilwoo/rt2_assignment1/tree/ros2/rt2_assignment1) needed for this assignement. These packages contains the nodes and the simulation environment for controlling a mobile robot in the Gazebo simulation environment.
There robot is controlled from the terminal by the user. Once the program starts the user will put as an input "1" for make the robot move toward a random position. The robot will reach the target and once it is reached it will automatically have another target to reach. If the user wants to stop the robot it is sufficient to type "0" in the terminal. The robot will stop once the current target is reached. If the user types "1" again the behaviour will start from the beginning.


## Nodes description
- ROS1 package: contains 2 python nodes:
  - [go_to_point](https://github.com/Marilwoo/rt2_assignment1/blob/main/scripts/go_to_point.py) : this node contains a publisher to the topic `/cmd_vel`, a subscriber to the topic `/odom` and a service for `/go_to_point`. The first one is used for publishing linear and angular velocity the robot has to move with; the second one is to retreive the actual position of the robot and the third one is used for receiving the target position the robot has to reach.
  - [user_interface](https://github.com/Marilwoo/rt2_assignment1/blob/main/scripts/user_interface.py) : this node is used for taking the user input from the terminal. It contains a client for `/user_interface`.

- ROS2 package: contains 2 cpp nodes

  - [position_service](https://github.com/Marilwoo/rt2_assignment1/blob/main/src/position_service.cpp) : this node is used for selecting the random position and orientation of the target the robot has to reach. It contains a seervice for `/position_server`. It takes as a request maximum and minimum values both for x and y position and replies random values in between these two. Also it replies with a random orientation between +pi and -pi
  - [state_machine](https://github.com/Marilwoo/rt2_assignment1/blob/main/src/state_machine.cpp) : This node contains a server for `/user_interface`, it takes the information about the input given from the user and, depending on it, it assigns a variable to `true` or `false`. It contains also a client for `/position_server` that sends as a request the max and min values for the target position. After that it uses the client for `/go_to_point` for sending the target position and making the robot reach it.

## Services, Messages and Actions
Both the packages contains the same three services:
- [Command](https://github.com/Marilwoo/rt2_assignment1/blob/ros2/rt2_assignment1/srv/Command.srv)
- [RandomPosition](https://github.com/Marilwoo/rt2_assignment1/blob/ros2/rt2_assignment1/srv/RandomPosition.srv)
- [Position](https://github.com/Marilwoo/rt2_assignment1/blob/ros2/rt2_assignment1/srv/Position.srv) 

## How to run
- Clone this repository into your ROS1 workspace
- Move the [ROS2 package](https://github.com/Marilwoo/rt2_assignment1/tree/ros2/rt2_assignment1) into the ROS2 workspace
- Check that the [mapping_rule.yaml](https://github.com/Marilwoo/rt2_assignment1/blob/ros2/rt2_assignment1/mapping_rule.yaml) file contains the right name for your packages
- Clone the [ros1_bridge](https://github.com/ros2/ros1_bridge) repository into your ROS2 workspace
- Move the three source files: [ros.sh](https://github.com/Marilwoo/rt2_assignment1/blob/ros2/ros.sh), [ros2.sh](https://github.com/Marilwoo/rt2_assignment1/blob/ros2/ros2.sh), [ros12.sh](https://github.com/Marilwoo/rt2_assignment1/blob/ros2/ros12.sh) into your root folder and check that the workspaces' names are correct, if not, change them.
- Go into your ros1 workspace and build the packages with.
```
catkin_make
```
- Go into your ROS2 workspace and build the packages skipping the ros1_bridge
 ```
colcon build --packages-skip ros1_bridge
 ```
- Build the ros1_bridge package (this may take a while)
```
colcon build --packages-select ros1_bridge --cmake-force-configure
 ```
- At this point you can run the nodes: you will need three terminals
  - In the first one run:
   ```
   source ros2.sh
   ros2 launch rt2_assignment1 sim_launch.py
   ```
   - In the second one run:
   ```
   source ros12.sh
   ros2 run ros1_bridge dynamic_bridge
   ```
   - In the third one run:
   ```
   source ros.sh
   roslaunch rt2_assignment1 sim.launch
   ```
- Now that everything is running you will find in the ROS1 terminal the instructions and you will be able to start the robot by typing the input.




