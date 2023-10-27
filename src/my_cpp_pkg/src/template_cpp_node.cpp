#include "rclcpp/rclcpp.hpp"

class SmartPhoneNode : public rclcpp::Node {
public:
    SmartPhoneNode() : Node("node_name") {

    }

private:

};

int main(int argc, char const* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmartPhoneNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

