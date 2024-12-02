#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "omuni/msg/joystick.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include <cmath>

class OmuniNode : public rclcpp::Node
{
public:
  OmuniNode()
  : Node("omuni_node")
  {
  
    joystick_sub_ = this->create_subscription<omuni::msg::Joystick>(
      "joystick", 10, std::bind(&OmuniNode::joystick_callback, this, std::placeholders::_1));

    
    motor_duty_pub_ = this->create_publisher<std_msgs::msg::Float32MultiArray>("motor_duty", 10);
  }

private:
  void joystick_callback(const omuni::msg::Joystick::SharedPtr msg)
  {
    
    float x = msg->left_joy_x;
    float y = msg->left_joy_y;
    float yaw = msg->right_joy_x;

    
    
    float v1 = x * std::cos(0) + y * std::sin(0) + yaw;
    float v2 = x * std::cos(2 * M_PI / 3) + y * std::sin(2 * M_PI / 3) + yaw;
    float v3 = x * std::cos(4 * M_PI / 3) + y * std::sin(4 * M_PI / 3) + yaw;

    

    
    std_msgs::msg::Float32MultiArray duty_msg;
    duty_msg.data.push_back(v1);
    duty_msg.data.push_back(v2);
    duty_msg.data.push_back(v3);

    
    motor_duty_pub_->publish(duty_msg);
  }

  rclcpp::Subscription<omuni::msg::Joystick>::SharedPtr joystick_sub_;
  rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr motor_duty_pub_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<OmuniNode>());
  rclcpp::shutdown();
  return 0;
}
