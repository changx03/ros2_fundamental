#include <string>
#include <sstream>
#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class AddTwoServerNode : public rclcpp::Node {  // Change class name
public:
    AddTwoServerNode() : Node("add_two_server") {  // Change class name
        server_ = this->create_service<example_interfaces::srv::AddTwoInts>(
            "add_two_ints",
            std::bind(&AddTwoServerNode::callbackAddTwoInts,
                this, std::placeholders::_1, std::placeholders::_2));
        RCLCPP_INFO(this->get_logger(), "Add Two Server has been started!");
    }

private:
    void callbackAddTwoInts(
        const example_interfaces::srv::AddTwoInts::Request::SharedPtr request,
        const example_interfaces::srv::AddTwoInts::Response::SharedPtr response) {
        response->sum = request->a + request->b;
        std::stringstream ss;
        // ss << request->a << " + " << request->b << " = " << response->sum;
        // RCLCPP_INFO(this->get_logger(), ss.str().c_str());
        RCLCPP_INFO(this->get_logger(), "%ld + %ld = %ld", request->a, request->b, response->sum);
    }

    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr server_;
};

int main(int argc, char const* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoServerNode>();  // Change class name
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
