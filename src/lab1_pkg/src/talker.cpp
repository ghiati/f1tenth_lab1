#include "rclcpp/rclcpp.hpp"
#include "ackermann_msgs/msg/ackermann_drive_stamped.hpp"

class TalkerNode : public rclcpp::Node 
{
public:
    TalkerNode() : Node("talker_node") 
    {
        this->declare_parameter("v", 0.0);
        this->declare_parameter("d", 0.0);

        publisher_ = this->create_publisher<ackermann_msgs::msg::AckermannDriveStamped>("drive", 10);

        timer_ = this->create_wall_timer(std::chrono::milliseconds(1000), std::bind(&TalkerNode::publish_message, this));
    }

private:
    void publish_message()
    {
        auto msg = ackermann_msgs::msg::AckermannDriveStamped();
        msg.drive.speed = this->get_parameter("v").as_double();
        msg.drive.steering_angle = this->get_parameter("d").as_double();
        publisher_->publish(msg);
    }

    rclcpp::Publisher<ackermann_msgs::msg::AckermannDriveStamped>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TalkerNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
