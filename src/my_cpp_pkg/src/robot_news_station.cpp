#include <string>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class SmartPhoneNode : public rclcpp::Node {
public:
    SmartPhoneNode() : Node("robot_news_station"), robot_name_("R2D2") {
        publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500),
            std::bind(&SmartPhoneNode::publishNews, this));
        RCLCPP_INFO(this->get_logger(), "Robot News Station has been started!");
    }

private:
    void publishNews() {
        auto msg = example_interfaces::msg::String();
        msg.data = "Hi, this is " + robot_name_ + " from the Robot News Station ^_^";
        publisher_->publish(msg);
    }

    std::string robot_name_;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

};

int main(int argc, char const* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmartPhoneNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
