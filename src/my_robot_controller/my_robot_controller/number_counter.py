import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64


class NumberCounter(Node):
    def __init__(self):
        super().__init__('num_counter')
        self.num_count_publisher_ = self.create_publisher(
            Int64, 'number_counter', 10)
        self.num_subscriber_ = self.create_subscription(
            Int64, 'number', self.callback_number, 10)
        self.get_logger().info("Number counter has been started!")

    def callback_number(self, msg):
        self.counter_ = msg.data
        next_msg = Int64()
        next_msg.data = self.counter_
        self.num_count_publisher_.publish(next_msg)
        self.get_logger().info(str(self.counter_))


def main(args=None):
    rclpy.init(args=args)
    node = NumberCounter()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
