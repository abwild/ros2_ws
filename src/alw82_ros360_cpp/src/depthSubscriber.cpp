// PHS: Template combining together publisher and subscriber examples

//General C++ includes as needed
#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <stdlib.h>

#include <math.h>

#include "cv_bridge/cv_bridge.h"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include <opencv2/opencv.hpp>

//ROS 2 Specific includes
//Important: these includes should be reflected in the package.xml and CMakeLists.txt
#include "rclcpp/rclcpp.hpp"

// TODO: Add or replace with message type needed
#include "std_msgs/msg/string.hpp" 
#include "geometry_msgs/msg/twist.hpp" 
#include "geometry_msgs/msg/point32.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"

using namespace std::chrono_literals;
using namespace std::placeholders;

/* Template giving outline for creating a program
 * that contains both a publisher and subscriber.
 */

class DepthPerception : public rclcpp::Node
{
public:

  int x;
  int y;
  
  DepthPerception() : Node("depth_perception")
  {

    img_subscription = this->create_subscription<sensor_msgs::msg::Image>(
      "/head_front_camera/depth_registered/image_raw", 
	  10, std::bind(&DepthPerception::image_callback, this, _1));
	  
	colour_subscription = this->create_subscription<geometry_msgs::msg::Point32>(
      "/colour_detection", 10, std::bind(&DepthPerception::colour_callback, this, _1));

	tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);
    
  }
  
  void colour_callback(const geometry_msgs::msg::Point32 & colMsg)
  {
	  x = (int)colMsg.x;
	  y = (int)colMsg.y;
  }
  
  void image_callback(const sensor_msgs::msg::Image & imgMsg) 
  {
	cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(imgMsg, sensor_msgs::image_encodings::TYPE_32FC1);
	
	float depth = cv_ptr->image.at<float>(y,x);
	rclcpp::Time timestamp = rclcpp::Time(imgMsg.header.stamp);
	
	geometry_msgs::msg::TransformStamped t;
	
	t.header.stamp = timestamp;
	t.header.frame_id = "head_front_camera_depth_frame";
	t.child_frame_id = "target_object";
	
	// TODO Calculate x and y offset
	/*
	w = 640
	h = 480
	d = depth
	x = x
	y = x
	f = 522.1910329546544
	*/
	
	float x_offset;
	float y_offset;

	x_offset = (-(((x-(640/2))/522.1910329546544) * depth));
	y_offset = (-(((y-(480/2))/522.1910329546544) * depth));
	
	RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 1000, 
    		 "x offset: %f", x_offset);
			 
	RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 1000, 
    		 "y offset: %f", y_offset);

	t.transform.translation.x = depth;
	t.transform.translation.y = x_offset;
	t.transform.translation.z = y_offset;
	
	tf2::Quaternion q;
	q.setRPY(0,0,0);
	t.transform.rotation.x = q.x();
	t.transform.rotation.y = q.y();
	t.transform.rotation.z = q.z();
	t.transform.rotation.w = q.w();
	
	tf_broadcaster_->sendTransform(t);
	
	cv::cvtColor(cv_ptr->image, cv_ptr->image, cv::COLOR_GRAY2RGB);
	cv::circle(cv_ptr->image, cv::Point(x,y), 10, CV_RGB(0,0,255), 2);
	
	cv::imshow("Depth Perception", cv_ptr->image);
	cv::waitKey(3);
  }
  
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr img_subscription;
  rclcpp::Subscription<geometry_msgs::msg::Point32>::SharedPtr colour_subscription;
  
private:
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
    
};

static const std::string OPENCV_WINDOW = "Depth Perception";


//Main method defining entry point for program
int main(int argc, char * argv[])
{
  //Initialise ROS 2 for this node
  rclcpp::init(argc, argv);

  //Create the instance of the Node subclass and 
  // start the spinner with a pointer to the instance
  rclcpp::spin(std::make_shared<DepthPerception>());
  //When the node is terminated, shut down ROS 2 for this node
  rclcpp::shutdown();
  return 0;
}
