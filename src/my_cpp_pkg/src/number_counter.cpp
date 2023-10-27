#include <string>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"


class NumberCounter : public rclcpp::Node {
public:
    NumberCounter() : Node("num_counter"), counter_(0) {
        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10,
            std::bind(&NumberCounter::callbackCounter, this, std::placeholders::_1));
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);
        RCLCPP_INFO(this->get_logger(), "Number counter has been started!");
    }

private:
    void callbackCounter(const example_interfaces::msg::Int64::SharedPtr msg) {
        counter_ += static_cast<long>(msg->data);
        auto next_msg = example_interfaces::msg::Int64();
        next_msg.data = counter_;
        publisher_->publish(next_msg);
        RCLCPP_INFO(this->get_logger(), "%ld", counter_);
    }

    long counter_;
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
