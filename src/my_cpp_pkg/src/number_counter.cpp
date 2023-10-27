#include <string>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"


class NumberCounter : public rclcpp::Node {
public:
    NumberCounter() : Node("num_counter") {
        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10,
            std::bind(&NumberCounter::callbackCounter, this, std::placeholders::_1));
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_counter", 10);
        RCLCPP_INFO(this->get_logger(), "Number counter has been started!");
    }

private:
    void callbackCounter(const example_interfaces::msg::Int64::SharedPtr msg) {
        auto next_msg = example_interfaces::msg::Int64();
        next_msg.data = msg->data;
        publisher_->publish(next_msg);
        std::string log = std::to_string(msg->data);
        RCLCPP_INFO(this->get_logger(), log.c_str());
    }

    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
};

int main(int argc, char const* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounter>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
