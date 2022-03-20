# Research Track 2 - First assignment - ROS2
##### Maria Luisa Aiachini - 4375373

## General behaviour
In this package you will find both [RIS1 package](https://github.com/Marilwoo/rt2_assignment1/tree/ros2) and [ROS2 package](https://github.com/Marilwoo/rt2_assignment1/tree/ros2/rt2_assignment1) needed for this assignement. These packages contains the nodes and the simulation environment for controlling a mobile robot in the Gazebo simulation environment.
There robot is controlled from the terminal by the user. Once the program starts the user will put as an input "1" for make the robot move toward a random position. The robot will reach the target and once it is reached it will automatically have another target to reach. If the user wants to stop the robot it is sufficient to type "0" in the terminal. The robot will stop once the current target is reached. If the user types "1" again the behaviour will start from the beginning.


## Nodes description
- ROS1 package: contains 2 python nodes:
  - [go_to_point](https://github.com/Marilwoo/rt2_assignment1/blob/main/scripts/go_to_point.py) : this node contains a publisher to the topic `/cmd_vel`, a subscriber to the topic `/odom` and a service for `/go_to_point`. The first one is used for publishing linear and angular velocity the robot has to move with; the second one is to retreive the actual position of the robot and the third one is used for receiving the target position the robot has to reach.
  - [user_interface](https://github.com/Marilwoo/rt2_assignment1/blob/main/scripts/user_interface.py) : this node is used for taking the user input from the terminal. It contains a client for `/user_interface`.

- Ros2 package: contains 2 cpp nodes

  - [position_service](https://github.com/Marilwoo/rt2_assignment1/blob/main/src/position_service.cpp) : this node is used for selecting the random position and orientation of the target the robot has to reach. It contains a seervice for `/position_server`. It takes as a request maximum and minimum values both for x and y position and replies random values in between these two. Also it replies with a random orientation between +pi and -pi
  - [state_machine](https://github.com/Marilwoo/rt2_assignment1/blob/main/src/state_machine.cpp) : This node contains a server for `/user_interface`, it takes the information about the input given from the user and, depending on it, it assigns a variable to `true` or `false`. It contains also a client for `/position_server` that sends as a request the max and min values for the target position. After that it uses the client for `/go_to_point` for sending the target position and making the robot reach it.

## Services, Messages and Actions
Both the packages contains the same three services
- [Command](https://github.com/Marilwoo/rt2_assignment1/blob/ros2/rt2_assignment1/srv/Command.srv)
- [RandomPosition](https://github.com/Marilwoo/rt2_assignment1/blob/ros2/rt2_assignment1/srv/RandomPosition.srv)
- [Position](https://github.com/Marilwoo/rt2_assignment1/blob/ros2/rt2_assignment1/srv/Position.srv) 

## How to run
At first you need to clone this repository in a ros workspace. Build the package in a ros1 sourced terminal running
```
catkin_make
```
- Run in a terminal with ros1 sourced:
 ```
 roslaunch rt2_assignment1 sim.launch
 ```
- Follow the nstrucions on the terminal





