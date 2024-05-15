#!/usr/env python3
import rclpy
from rclpy.node import Node
from ackermann_msgs.msg import AckermannDriveStamped

class RelayNode(Node):
    def __init__(self):
        super().__init__('relay_node')

        self.subscription = self.create_subscription(
            AckermannDriveStamped,
            'drive',
            self.callback,
            10
        )
        self.subscription

        self.publisher = self.create_publisher(AckermannDriveStamped, 'drive_relay', 10)

    def callback(self, msg):
        msg.drive.speed *= 3
        msg.drive.steering_angle *= 3
        self.publisher.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    relay_node = RelayNode()
    rclpy.spin(relay_node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()



