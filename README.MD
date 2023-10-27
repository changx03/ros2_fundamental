# ROS2 Fundamental Projects

This is the coding project for ROS2 tutorial series by Edouard Renard.

## Get started


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

Each topic contains publishers and subscribers.\
Multiple publishers with the same `topic_name` is allowed.

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

```
