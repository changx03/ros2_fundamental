#include "rclcpp/rclcpp.hpp"

class TemplateNode : public rclcpp::Node {  // Change class name
public:
    TemplateNode() : Node("node_name") {  // Change class name

    }

private:

};

int main(int argc, char const* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TemplateNode>();  // Change class name
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

