import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist


class DrawCircle(Node):
    def __init__(self):
        super().__init__('draw_circle')
        self.cmd_val_pub_ = self.create_publisher(
            Twist, '/turtle1/cmd_vel', 10)
        self.timer_ = self.create_timer(.5, self.send_velocity_callback)
        self.get_logger().info('Draw circle node has initiated!')

    def send_velocity_callback(self):
        msg = Twist()
        msg.linear.x = 2.
        msg.angular.z = 1.
        self.cmd_val_pub_.publish(msg)


def main(args=None):
    rclpy.init(args=args)
    node = DrawCircle()
    rclpy.spin(node)
    rclpy.shutdown()
