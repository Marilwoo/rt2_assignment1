# Research Track 2 - First assignment - CoppeliaSim
##### Maria Luisa Aiachini - 4375373

## General behaviour
The package contains the nodes and the simulation environment for controlling a mobile robot both in the Gazebo simulation environment and in CoppeliaSim.
There robot is controlled from the terminal by the user. Once the program starts the user will put as an input "1" for make the robot move toward a random position. The robot will reach the target and once it is reached it will automatically have another target to reach. If the user wants to stop the robot it is sufficient to type "0" in the terminal. The robot will stop itself once the current target is reached. If the user types "1" again the behaviour will start from the beginning.


## Nodes description
The package contains 4 nodes, two python nodes
- [go_to_point](https://github.com/Marilwoo/rt2_assignment1/blob/main/scripts/go_to_point.py) : this node contains a publisher to the topic `/cmd_vel`, a subscriber to the topic `/odom` and a service for `/go_to_point`. The first one is used for publishing linear and angular velocity the robot has to move with; the second one is to retreive the actual position of the robot and the third one is used for receiving the target position the robot has to reach.
- [user_interface](https://github.com/Marilwoo/rt2_assignment1/blob/main/scripts/user_interface.py) : this node is used for taking the user input from the terminal. It contains a client for `/user_interface`.
and two cpp nodes
- [position_service](https://github.com/Marilwoo/rt2_assignment1/blob/main/src/position_service.cpp) : 
- [state_machine](https://github.com/Marilwoo/rt2_assignment1/blob/main/src/state_machine.cpp) : 



## How to run

To launch the node, please run:
```
roslaunch rt2_assignment1 sim.launch
```

