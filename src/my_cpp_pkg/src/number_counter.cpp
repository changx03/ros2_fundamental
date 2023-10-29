#include <string>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/int64.hpp"
#include "example_interfaces/srv/set_bool.hpp"


class NumberCounter : public rclcpp::Node {
public:
    NumberCounter() : Node("num_counter"), counter_(0) {
        subscriber_ = this->create_subscription<example_interfaces::msg::Int64>(
            "number", 10,
            std::bind(&NumberCounter::callbackCounter, this, std::placeholders::_1));
        publisher_ = this->create_publisher<example_interfaces::msg::Int64>("number_count", 10);
        server_ = this->create_service<example_interfaces::srv::SetBool>(
            "reset_number_counter",
            std::bind(&NumberCounter::callbackResetCounter,
                this, std::placeholders::_1, std::placeholders::_2));
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

    void callbackResetCounter(
        const example_interfaces::srv::SetBool::Request::SharedPtr request,
        const example_interfaces::srv::SetBool::Response::SharedPtr response) {
        if (request->data) {
            counter_ = 0;
            response->success = true;
            response->message = "Successfully reset the counter!";
        }
        else {
            response->success = false;
            response->message = "Counter has not been reset";
        }

    }

    long counter_;
    rclcpp::Subscription<example_interfaces::msg::Int64>::SharedPtr subscriber_;
    rclcpp::Publisher<example_interfaces::msg::Int64>::SharedPtr publisher_;
    rclcpp::Service<example_interfaces::srv::SetBool>::SharedPtr server_;
};

int main(int argc, char const* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<NumberCounter>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
