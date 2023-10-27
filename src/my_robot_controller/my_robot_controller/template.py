import rclpy
from rclpy.node import Node


class MyCustomNode(Node):  # Update class name
    def __init__(self):
        super().__init__('node_name')  # Update node name


def main(args=None):
    rclpy.init(args=args)
    node = MyCustomNode()  # Update class name
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
