#!/bin/bash

gnome-terminal --tab --title="ros1" -- bash -c "source ros.sh; roslaunch rt2_assignment1 sim.launch"
gnome-terminal --tab --title="ros_bridge" -- bash -c "sleep 2; source ros12.sh; ros2 run ros1_bridge dynamic_bridge"
gnome-terminal --tab --title="ros2" -- bash -c "source ros2.sh; ros2 launch rt2_assignment1 sim_launch.py"
