import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64
from example_interfaces.srv import SetBool


class NumberCounter(Node):
    def __init__(self):
        super().__init__('num_counter')
        self.num_count_publisher_ = self.create_publisher(
            Int64, 'number_counter', 10)
        self.num_subscriber_ = self.create_subscription(
            Int64, 'number', self.callback_number, 10)
        self.counter_ = 0
        self.service_ = self.create_service(
            SetBool, 'reset_number_counter', self.callback_reset_counter)
        self.get_logger().info("Number counter has been started!")

    def callback_number(self, msg):
        self.counter_ += msg.data
        next_msg = Int64()
        next_msg.data = self.counter_
        self.num_count_publisher_.publish(next_msg)
        self.get_logger().info(str(self.counter_))

    def callback_reset_counter(self, request, response):
        if request.data:
            self.counter_ = 0
            response.success = True
            response.message = "Successfully reset the counter!"
        else:
            response.success = False
            response.message = "Counter has not been reset!"
        return response


def main(args=None):
    rclpy.init(args=args)
    node = NumberCounter()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
