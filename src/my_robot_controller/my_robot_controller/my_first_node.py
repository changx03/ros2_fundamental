import rclpy
from rclpy.node import Node


class MyAwesomeNode(Node):
    def __init__(self, ) -> None:
        super().__init__('my_cool_node')
        self.create_timer(1.0, self.timer_callback)

    def timer_callback(self):
        self.get_logger().info('Hello from my ROS AWESOME node!')


def main(args=None):
    rclpy.init(args=args)

    # Start your node here :>
    node = MyAwesomeNode()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
