#include "rclcpp/rclcpp.hpp"
#include "ackermann_msgs/msg/ackermann_drive_stamped.hpp"

class Relayer : public rclcpp::Node
{
public:
    Relayer() : Node("relayer")
    {
        publisher_ = this->create_publisher<ackermann_msgs::msg::AckermannDriveStamped>("drive_relay", 10);
        subscription_ = this->create_subscription<ackermann_msgs::msg::AckermannDriveStamped>(
            "drive", 10, std::bind(&Relayer::topic_callback, this, std::placeholders::_1));
    }

private:
    void topic_callback(const ackermann_msgs::msg::AckermannDriveStamped::SharedPtr msg)
    {
        auto message = ackermann_msgs::msg::AckermannDriveStamped();
        message.drive.speed = msg->drive.speed * 3;
        message.drive.steering_angle = msg->drive.steering_angle * 3;
        publisher_->publish(message);
    }
    rclcpp::Publisher<ackermann_msgs::msg::AckermannDriveStamped>::SharedPtr publisher_;
    rclcpp::Subscription<ackermann_msgs::msg::AckermannDriveStamped>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Relayer>());
    rclcpp::shutdown();
    return 0;
}