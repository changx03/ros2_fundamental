# ROS2 Fundamental Projects

This is the coding project for ROS2 tutorial series by Edouard Renard.

## Get started

### Start from an empty folder

To create a new package (**This code has already created multiple packages**)

```bash
# For a python package
ros2 pkg create <pkg_name> --build-type ament_python

# For a C++ package
ros2 pkg create <pkg_name> --build-type ament_cpp
```

If encounter a deprecated error on `setup.py`, run `pip install --upgrade setuptools==58.2.0`

---

### For this repo

Starts from here

```bash
# Add dependencies to the terminal
source ./ros2.sh

# Initial build
colcon build
```

Add packages dependencies to `./ros2.sh` file:

```bash
source <workspace_directory>/install/setup.bash
```

### Build package

To build all packages:

```bash
colcon build --symlink-install
```

To build a specific package:

```bash
colcon build --symlink-install --packages-select <pkg_name>
```

The `symlink-install` flag provides runtime updates.

### Run a node

```bash
ros2 run <pkg_name> <node_name>

# e.g.
ros2 run my_robot_controller my_first_node
```

### Other commands

```bash
# Graph GUI
rqt_graph

# Show running nodes
ros2 node list

# Show node info
ros2 node info /<node_name>

# Rename a node (This allows you to create multiple instances of the same node)
ros2 run <pkg_name> <node_name> --ros_args --remap __node:=<new_node_name>
```

## Topic

- Topics are used for data streaming.
- Topics do not wait for response.
- Multiple publishers and subscribers can attach to the same topic.
- Multiple publishers with the same `topic_name` is allowed.

```bash
# Show running topics
ros2 topic list

# Show topic info
ros2 topic info /<topic_name>

# Subscribe a topic from the terminal
ros2 topic echo /<topic_name>

# Publish a topic from the terminal
ros2 topic pub -r <hz> /<topic_name> <topic_interface> "<topic_content>"

# e.g.
ros2 topic pub -r 10 /robot_news example_interfaces/msg/String "{data: 'Hello from terminal'}"

# Get frequency
ros2 topic hz /<topic_name>

# Print the interface of a topic
ros2 interface show example_interfaces/msg/String

# Remap topic name
# This works for both publisher and subscriber
ros2 run my_cpp_pkg robot_news_station --ros-args --remap <topic_name>:=<new_topic_name>

# e.g., for publisher
ros2 run my_cpp_pkg robot_news_station --ros-args --remap robot_news:=my_news
# for subscriber
ros2 run my_cpp_pkg smartphone --ros-args --remap robot_news:=my_news

```

## Service

- Services are used for client/server interactions.

```bash
ros2 service list

# Create a service call
ros2 service call <service_name> <service_interface> "<request_values>"

# e.g.
ros2 service call /add_two_ints example_interfaces/srv/AddTwoInts "{a: 3, b: 4}"

# Get service interface
ros2 service type <service_name>

# Get parameters for the interface (For both request and response)
ros2 interface show <interface_name>

# Remap service name
ros2 run <pkg_name> <node_name> --ros-args --remap <service_name>:=<new_service_name>
```

Use `rtq` to create service call in the GUI.
