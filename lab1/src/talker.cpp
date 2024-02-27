#include "rclcpp/rclcpp.hpp"
#include "ackermann_msgs/msg/ackermann_drive_stamped.hpp"

class Talker : public rclcpp::Node
{
public:
    Talker() : Node("talker"), count_(0)
    {
        publisher_ = this->create_publisher<ackermann_msgs::msg::AckermannDriveStamped>("drive", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(1),
            std::bind(&Talker::timer_callback, this));
        this->declare_parameter<double>("v", 0.0);
        this->declare_parameter<double>("d", 0.0);
    }

private:
    void timer_callback()
    {
        auto message = ackermann_msgs::msg::AckermannDriveStamped();
        this->get_parameter("v", message.drive.speed);
        this->get_parameter("d", message.drive.steering_angle);
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<ackermann_msgs::msg::AckermannDriveStamped>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Talker>());
    rclcpp::shutdown();
    return 0;
}