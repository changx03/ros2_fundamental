#include <string>
#include "rclcpp/rclcpp.hpp"

class MyNode : public rclcpp::Node {
public:
    MyNode() : Node("cpp_test"), counter_(0), name_("CPP Node") {
        this->counter_ = 0;
        RCLCPP_INFO(this->get_logger(), "Hello %s!", name_.c_str());

        timer_ = this->create_wall_timer(std::chrono::seconds(1),
            std::bind(&MyNode::timerCallback, this)
        );
    }

private:
    void timerCallback() {
        counter_++;
        RCLCPP_INFO(this->get_logger(), "Hello %d", counter_);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;
    std::string name_;
};


int main(int argc, char const* argv[]) {
    rclcpp::init(argc, argv);
    // auto node = std::make_shared<rclcpp::Node>("cpp_test");
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
