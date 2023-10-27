from functools import partial

import rclpy
from rclpy.node import Node
from rclpy.task import Future
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
from turtlesim.srv import SetPen


class TurtleControllerNode(Node):
    def __init__(self):
        super().__init__('turtle_ctrl')
        self.previous_x_ = 0.
        self.cmd_vel_pub_ = self.create_publisher(
            Twist,
            '/turtle1/cmd_vel',
            10
        )
        self.pose_sub_ = self.create_subscription(
            Pose,
            '/turtle1/pose',
            self.pose_callback,
            10
        )

        self.get_logger().info('Turtle Controller has been started!')

    def pose_callback(self, pose: Pose):
        cmd = Twist()
        if pose.x > 9. or pose.x < 2. or pose.y > 9. or pose.y < 2.:
            cmd.linear.x = 1.
            cmd.angular.z = 0.9
        else:
            cmd.linear.x = 5.
            cmd.angular.z = 0.
        self.cmd_vel_pub_.publish(cmd)

        if pose.x > 5.5 and self.previous_x_ <= 5.5:
            self.get_logger().info('Set color to RED')
            self.call_set_pen_srv(255, 0, 0, 3, 0)
        elif pose.x <= 5.5 and self.previous_x_ > 5.5:
            self.get_logger().info('Set color to GREEN')
            self.call_set_pen_srv(0, 255, 0, 3, 0)
        self.previous_x_ = pose.x

    def call_set_pen_srv(self, r: int, g: int, b: int, width: int, off: int):
        client = self.create_client(SetPen, '/turtle1/set_pen')
        while not client.wait_for_service(1.):
            # Wait until the service is ready
            self.get_logger().warn('Waiting for service...')

        request = SetPen.Request()
        request.r = r
        request.g = g
        request.b = b
        request.width = width
        request.off = off

        future = client.call_async(request)
        future.add_done_callback(partial(self.callback_set_pen))

    def callback_set_pen(self, future: Future):
        try:
            res = future.result()
        except Exception as e:
            self.get_logger().error(f'Service call failed: {e}')


def main(args=None):
    rclpy.init(args=args)
    node = TurtleControllerNode()
    rclpy.spin(node)
    rclpy.shutdown()
