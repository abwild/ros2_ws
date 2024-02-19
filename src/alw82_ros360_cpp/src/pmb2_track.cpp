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

class TrackRobot : public rclcpp::Node
{
public:

  float leftVals [40];
  float rightVals [40];
  float centVals [40];
  float leftTotal = 0;
  float rightTotal = 0;
  float centTotal = 0;
  
  TrackRobot() : Node("track_follower")
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/servoing_cmd_vel", 10);

    subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
      "/scan_raw", 10, std::bind(&TrackRobot::topic_callback, this, _1));

    timer_ = this->create_wall_timer(
      100ms, std::bind(&TrackRobot::timer_callback, this));
  }

private:

  void timer_callback()
  {
    auto message = geometry_msgs::msg::Twist();
	
    float difference = leftTotal - rightTotal;
    RCLCPP_INFO_THROTTLE(this->get_logger(),
     *this->get_clock(), 
     1000, 
     "Difference: %f", difference);

    message.angular.z = difference*0.9;
	message.linear.x = (centTotal/10)*4.0;
	
    publisher_->publish(message);
  }

  //TODO rename method to better reflect topic it is subscribed to
  //TODO update message type as appropriate
  void topic_callback(const sensor_msgs::msg::LaserScan & msg) 
  {

    
    
    for(int i=86; i>46; i--){
    	if(!isinf(msg.ranges[i])){
    		rightVals[86-i] = msg.ranges[i];
    		/*RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 500, 
    		 "Left value '%d': %f", i, msg.ranges[i]);*/
    	}
    }
    
    for(int i=620; i>580; i--){
    	if(!isinf(msg.ranges[i])){
    		leftVals[620-i] = msg.ranges[i];
    		/*RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 500, 
    		 "Right value '%d': %f", i, msg.ranges[i]);*/
    	}
    }
    
    for(int i=340; i>300; i--){
    	if(!isinf(msg.ranges[i])){
    		centVals[340-i] = msg.ranges[i];
    	}
    }
    
    //averaging
    
    for(float f : leftVals){
    leftTotal += f;
    }
    for(int i=0; i<40; i++){
    rightTotal += rightVals[i];
    }
    for(float f : centVals){
    centTotal += f;
    }
    
    leftTotal /= (sizeof(leftVals)/sizeof(leftVals[0]));
    rightTotal /= (sizeof(rightVals)/sizeof(rightVals[0]));
    centTotal /= (sizeof(centVals)/sizeof(centVals[0]));
    
    RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 1000, 
    		 "Right total: %f", rightTotal);
    
    RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 1000, 
    		 "Left total: %f", leftTotal);
    		 
    RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 1000, 
    		 "Centre total: %f", centTotal);
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
  rclcpp::spin(std::make_shared<TrackRobot>());
  //When the node is terminated, shut down ROS 2 for this node
  rclcpp::shutdown();
  return 0;
}
