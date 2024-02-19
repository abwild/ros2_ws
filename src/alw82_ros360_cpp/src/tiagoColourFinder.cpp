// PHS: Template combining together publisher and subscriber examples

//General C++ includes as needed
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <stdlib.h>

#include <math.h>

//ROS 2 Specific includes
//Important: these includes should be reflected in the package.xml and CMakeLists.txt
#include "rclcpp/rclcpp.hpp"

// TODO: Add or replace with message type needed
#include "std_msgs/msg/string.hpp" 
#include "geometry_msgs/msg/twist.hpp" 
#include "geometry_msgs/msg/point32.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

/* Template giving outline for creating a program
 * that contains both a publisher and subscriber.
 */

class TiagoColourFinder : public rclcpp::Node
{
public:

  long int ranges_b[3] = {255,14,27};
  long int ranges_g[3] = {10,255,10};
  long int ranges_r[3] = {45,35,255};
  
  //long int all_ranges[3][3] = {{255,50,50}, {50,255,20}, {50,50,255}};
  

  bool foundSomething = false;
  float adjustingValue;
  float forwardValue;
  
  TiagoColourFinder() : Node("tiago_colour_finder")
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/servoing_cmd_vel", 10);

    subscription_ = this->create_subscription<geometry_msgs::msg::Point32>(
      "/colour_detection", 10, std::bind(&TiagoColourFinder::topic_callback, this, _1));

    timer_ = this->create_wall_timer(
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
      
	  /*if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), future) ==
        rclcpp::FutureReturnCode::SUCCESS)
      {
        auto response = future.get();
        for(auto result : response->results)
        {
          RCLCPP_INFO(this->get_logger(), "Result of colour params update: %d", result.successful);
        }
        
      } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service /colour_detector/set_parameters");
      }*/
	
    }

private:

  void timer_callback()
  {
    auto message = geometry_msgs::msg::Twist();
	
	if(!foundSomething){
		message.angular.z = 0.5;
	}
	if(foundSomething){
		message.angular.z = adjustingValue;
		message.linear.x = forwardValue;
    }		
    publisher_->publish(message);
  }

  //TODO rename method to better reflect topic it is subscribed to
  //TODO update message type as appropriate
  void topic_callback(const geometry_msgs::msg::Point32 & msg) 
  {
	foundSomething = true;
    if(msg.x != 320){
		adjustingValue = (320 - msg.x)/200;
	}else{
		adjustingValue = 0.0;
    }
	
	if(adjustingValue > 1.0){
		adjustingValue = 1.0;
	}else if(adjustingValue < -1.0){
		adjustingValue = -1.0;
	}
	
	if((adjustingValue <= 0.1 && adjustingValue > 0)
		|| (adjustingValue < 0 && adjustingValue >= -0.1)){
		forwardValue = (480 - msg.y)/100;
	}

	if(msg.y >= 475){
		adjustingValue = 0.0;
		int random = rand() % 3;
		if(random == 0){
			send_request(ranges_b);
		}else if(random == 1){
			send_request(ranges_g);
		}else{
			send_request(ranges_r);
		}
		foundSomething = false;
	}
	
	RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 1000, 
    		 "Adjusting Value: %f", adjustingValue);
			 
	RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 1000, 
    		 "Forward Value: %f", forwardValue);
  }
 
  //Declaration of private fields used for timer, publisher and subscriber
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::Subscription<geometry_msgs::msg::Point32>::SharedPtr subscription_;
};

//Main method defining entry point for program
int main(int argc, char * argv[])
{
  //Initialise ROS 2 for this node
  rclcpp::init(argc, argv);

  //Create the instance of the Node subclass and 
  // start the spinner with a pointer to the instance
  rclcpp::spin(std::make_shared<TiagoColourFinder>());
  //When the node is terminated, shut down ROS 2 for this node
  rclcpp::shutdown();
  return 0;
}
