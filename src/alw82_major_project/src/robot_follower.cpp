//General C++ includes as needed
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <stdlib.h>

#include <math.h>

#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/string.hpp" 
#include "geometry_msgs/msg/twist.hpp" 
#include "geometry_msgs/msg/point32.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;


class TiagoColourFinder : public rclcpp::Node
{
public:

  long int ranges_b[3] = {255,14,27};
  long int ranges_g[3] = {10,255,10};
  long int ranges_r[3] = {45,35,255};

  float adjustingValue;
  float forwardValue;
  
  TiagoColourFinder() : Node("tiago_colour_finder")
  {
    drive_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/traethlin/cmd_vel", 10);

    image_subscription_ = this->create_subscription<geometry_msgs::msg::Point32>(
      "/colour_detection", 10, std::bind(&TiagoColourFinder::image_callback, this, _1));

    adjustment_timer_ = this->create_wall_timer(
      100ms, std::bind(&TiagoColourFinder::timer_callback, this));

  }
  
  void send_request(long int *ranges)
    {
      auto parameter = rcl_interfaces::msg::Parameter();
      auto request = std::make_shared<rcl_interfaces::srv::SetParameters::Request>();

      auto client = this->create_client<rcl_interfaces::srv::SetParameters>("/colour_detector/set_parameters");

      parameter.name = "upper_limits";
      parameter.value.type = 7;
      parameter.value.integer_array_value = std::vector<long int>{ranges[0], ranges[1], ranges[2]};

      request->parameters.push_back(parameter);

      while (!client->wait_for_service(1s)) {
          if (!rclcpp::ok()) {
          RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
          return;
          }
          RCLCPP_INFO_STREAM(this->get_logger(), "service not available, waiting again..."); 
      }
      auto future = client->async_send_request(request);
    }

  private:

    void timer_callback()
    {
      auto message = geometry_msgs::msg::Twist();
      message.angular.z = adjustingValue;
      message.linear.x = forwardValue;
      drive_publisher_->publish(message);
    }

    void image_callback(const geometry_msgs::msg::Point32 & msg) 
    {
      /*320 is all the way right and 0 is far left */
      if(msg.x != 160){
        adjustingValue = (160 - msg.x)/200;
      }else{
        adjustingValue = 0.0;
      }
      /* checked first in the case that we lose the robot */
      if(msg.z < 1.0){
        forwardValue = 0.0;
      }else{
        if(msg.z <= 27.5){ /* 27.5 on z is close*/
          forwardValue = (12.5 / msg.z);
        }else if(msg.z > 27.5){
          forwardValue = 0.0;
        }
      }      
    }
  
    rclcpp::TimerBase::SharedPtr adjustment_timer_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr drive_publisher_;
    rclcpp::Subscription<geometry_msgs::msg::Point32>::SharedPtr image_subscription_;
  };

  int main(int argc, char * argv[])
  {
    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<TiagoColourFinder>());

    rclcpp::shutdown();
    return 0;
  }
