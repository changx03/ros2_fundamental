import rclpy
from rclpy.node import Node
from example_interfaces.msg import String


class MySubscriberNode(Node):
    def __init__(self):
        super().__init__('py_sub')
        self.cmd_val_pub_ = self.create_subscription(
            String,
            'robot_news',
            self.pose_callback,
            10
        )
        self.get_logger().info('My subscriber has been started!')

    def pose_callback(self, message: String):
        self.get_logger().info(f'Received: {message.data}')


def main(args=None):
    rclpy.init(args=args)
    node = MySubscriberNode()
    rclpy.spin(node)
    rclpy.shutdown()
