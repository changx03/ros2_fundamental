#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

class AddTwoClient : public rclcpp::Node {
public:
    AddTwoClient() : Node("add_two_client2") {
        threads_.push_back(std::thread(std::bind(&AddTwoClient::callAddTwoService, this, 1, 4)));
        threads_.push_back(std::thread(std::bind(&AddTwoClient::callAddTwoService, this, 2, 5)));
        threads_.push_back(std::thread(std::bind(&AddTwoClient::callAddTwoService, this, 3, 6)));
    }

    void callAddTwoService(int a, int b) {
        auto client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
        while (!client->wait_for_service(std::chrono::seconds(1))) {
            RCLCPP_WARN(this->get_logger(), "Waiting for the server to be up...");
        }
        auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
        request->a = a;
        request->b = b;

        auto future = client->async_send_request(request);
        try {
            auto response = future.get();
            RCLCPP_INFO(this->get_logger(), "%d + %d = %d",
                a, b, static_cast<int>(response->sum));
        }
        catch (const std::exception& e) {
            RCLCPP_ERROR(this->get_logger(), "Error while calling the service!");
        }
    }

private:
    std::vector<std::thread> threads_;  // Create a thread pool
};

int main(int argc, char const* argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoClient>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
