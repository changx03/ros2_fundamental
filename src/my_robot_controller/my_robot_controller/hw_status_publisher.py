import rclpy
from rclpy.node import Node

from my_interfaces.msg import HardwareStatus


class HardwareStatusPublisher(Node):
    def __init__(self):
        super().__init__('hw_status_publisher')
        self.hw_status_publisher_ = self.create_publisher(
            HardwareStatus, 'hw_status', 10)
        self.timer_ = self.create_timer(1.0, self.publish_hw_status)
        self.get_logger().info("Hardware status publisher has been started!")

    def publish_hw_status(self):
        msg = HardwareStatus()
        msg.temperature = 45
        msg.are_motors_ready = True
        msg.debug_msg = "Everything is ok!"
        self.hw_status_publisher_.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = HardwareStatusPublisher()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == "__main__":
    main()
