# ROS2 Fundamental Projects

This is the coding project for ROS2 tutorial series by Edouard Renard.

## Get started

Add dependencies to the terminal:

```bash
source ./ros2.sh
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

### Run a node

```bash
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

# Show running topics
ros2 topic list

# Show topic info
ros2 topic info /<topic_name>

# Print data from a topic
ros2 topic echo /<topic_name>

# Show running services
ros2 service list

# Rename a node (This allows you to create multiple instances of the same node)
ros2 run <pkg_name> <node_name> --ros_args --remap __node:=<new_node_name>
```
