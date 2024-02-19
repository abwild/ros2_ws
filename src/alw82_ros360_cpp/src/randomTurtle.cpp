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
#include "sensor_msgs/msg/laser_scan.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

/* Template giving outline for creating a program
 * that contains both a publisher and subscriber.
 */

class PubSubTemplate : public rclcpp::Node
{
public:

  float leftVals [10];
  float rightVals [10];
  
  //float RandomNumber(float Min, float Max)
  //{
   // return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
  //}
  
  //float x = RandomNumber(0.0, 1.0);
  //float y = RandomNumber(-0.5, 0.5);
  
  //TODO: Update node name to reflect purpose of node
  PubSubTemplate() : Node("pub_sub_template")
  {
    // TODO: Update message type and topic name as appropriate
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel", 10);

    // TODO: Update message type and topic name as appropriate
    subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
      "/scan", 10, std::bind(&PubSubTemplate::topic_callback, this, _1));
    
    // Create a timer that will trigger calls to the method timer_callback
    // TODO: Update timer duration as required
    timer_ = this->create_wall_timer(
      1000ms, std::bind(&PubSubTemplate::timer_callback, this));
  }

private:

  void timer_callback()
  {
    //TODO add behaviour here to be repeated at regular intervals

    //x = RandomNumber(0.0, 1.0);
    //y = RandomNumber(-0.5, 0.5);
    //Create an instance of the appropriate message type
    auto message = geometry_msgs::msg::Twist();

    //Set the values for necessary fields in message type
    //message.linear.x = x;
    //message.angular.z = y;

    //Log output for message to be published
    //RCLCPP_INFO(this->get_logger(), "Publishing: '%f' '%f'", message.linear.x, message.angular.z);

    //publish the message to topic
    publisher_->publish(message);
  }

  //TODO rename method to better reflect topic it is subscribed to
  //TODO update message type as appropriate
  void topic_callback(const sensor_msgs::msg::LaserScan & msg) 
  {

    
    
    for(int i=0; i<9; i++){
    	if(!isinf(msg.ranges[i])){
    		leftVals[i] = msg.ranges[i];
    		/*RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 500, 
    		 "Left value '%d': %f", i, msg.ranges[i]);*/
    	}
    }
    
    for(int i=358; i>348; i--){
    	if(!isinf(msg.ranges[i])){
    		rightVals[358-i] = msg.ranges[i];
    		/*RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 500, 
    		 "Right value '%d': %f", i, msg.ranges[i]);*/
    	}
    }
    
    //averaging
    float leftTotal = 0;
    float rightTotal = 0;
    for(float f : leftVals){
    	leftTotal += f;
    }
    for(float f : rightVals){
    	rightTotal += f;
    }
    leftTotal /= 10;
    rightTotal /= 10;
    RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 500, 
    		 "Right total: %f", rightTotal);
    
    RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 500, 
    		 "Left total: %f", leftTotal);
    		 
    auto message = geometry_msgs::msg::Twist();
    
    if(leftTotal <= 1.0){
    	message.angular.z = -1;
    }
    if(rightTotal <= 1.0){
    	message.angular.z = 1;
    }
    
    message.linear.x = 0.25;
    
    publisher_->publish(message);
    
    /*for(int i=0; i<360; i++){
    
    	if(!isinf(msg.ranges[i])){
    		RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 500, 
    		 "Detecting on: '%d':", i);
    	}
    }*/
    
    
    
  }

  //Declaration of private fields used for timer, publisher and subscriber
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr subscription_;
};

//Main method defining entry point for program
int main(int argc, char * argv[])
{
  //Initialise ROS 2 for this node
  rclcpp::init(argc, argv);

  //Create the instance of the Node subclass and 
  // start the spinner with a pointer to the instance
  rclcpp::spin(std::make_shared<PubSubTemplate>());

  //When the node is terminated, shut down ROS 2 for this node
  rclcpp::shutdown();
  return 0;
}
