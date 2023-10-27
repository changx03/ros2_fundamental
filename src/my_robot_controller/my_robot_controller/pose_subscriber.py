import rclpy
from rclpy.node import Node
from turtlesim.msg import Pose


class PoseSubscriberNode(Node):
    def __init__(self):
        super().__init__('sub_pose')
        self.cmd_val_pub_ = self.create_subscription(
            Pose,
            '/turtle1/pose',
            self.pose_callback,
            10
        )

    def pose_callback(self, msg: Pose):
        self.get_logger().info(f'Received: [{msg.x:.2f}, {msg.y:.2f}]')


def main(args=None):
    rclpy.init(args=args)
    node = PoseSubscriberNode()
    rclpy.spin(node)
    rclpy.shutdown()
