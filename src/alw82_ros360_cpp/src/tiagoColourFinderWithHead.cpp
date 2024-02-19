// PHS: Template combining together publisher and subscriber examples

//General C++ includes as needed
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <future>
#include <sstream>

#include <stdlib.h>

#include <math.h>

//ROS 2 Specific includes
//Important: these includes should be reflected in the package.xml and CMakeLists.txt
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "control_msgs/action/follow_joint_trajectory.hpp"
#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"

// TODO: Add or replace with message type needed
#include "std_msgs/msg/string.hpp" 
#include "geometry_msgs/msg/twist.hpp" 
#include "geometry_msgs/msg/point32.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "tf2/exceptions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"

using namespace std::chrono_literals;
using namespace std::placeholders;

/* Template giving outline for creating a program
 * that contains both a publisher and subscriber.
 */

class TiagoColourFinder : public rclcpp::Node
{
using FollowJointTrajectory = control_msgs::action::FollowJointTrajectory;
using GoalHandleFJT = rclcpp_action::ClientGoalHandle<FollowJointTrajectory>;
public:

  long int ranges_b[3] = {255,14,27};
  long int ranges_g[3] = {10,255,10};
  long int ranges_r[3] = {45,35,255};

  bool finished = false;

  bool foundSomething = false;
  float adjustingValue;
  float forwardValue;

  float headAdjustingValue = 0.0;
  
  TiagoColourFinder() : Node("tiago_colour_finder")
  {
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/servoing_cmd_vel", 10);

    subscription_ = this->create_subscription<geometry_msgs::msg::Point32>(
      "/colour_detection", 10, std::bind(&TiagoColourFinder::topic_callback, this, _1));

    timer_ = this->create_wall_timer(
      100ms, std::bind(&TiagoColourFinder::timer_callback, this));

    //target_frame_ = this->declare_parameter<std::string("target_frame", "target_object");

    tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());

    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

    this->client_ptr_ = rclcpp_action::create_client<FollowJointTrajectory>(this, "head_controller/follow_joint_trajectory");

    head_timer_ = this->create_wall_timer(2000ms, std::bind(&TiagoColourFinder::head_timer, this));

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
	
	if(!foundSomething){
		message.angular.z = 0.5;
	}
	if(foundSomething){
		message.angular.z = adjustingValue;
		message.linear.x = forwardValue;
    }		
    publisher_->publish(message);

    std::string fromFrame = "target_object";
    std::string toFrame = "base_link";

    geometry_msgs::msg::TransformStamped t;

    try{
      t = tf_buffer_->lookupTransform(toFrame, fromFrame, tf2::TimePointZero);
      if(t.transform.translation.x <= 0.6){
        finished = true;
      }
    } catch (const tf2::TransformException & ex){
      RCLCPP_INFO(this->get_logger(), "Could not find transform");
      return;
    }
  }

  void head_timer()
  {
    using namespace std::placeholders;

    if (!this->client_ptr_->wait_for_action_server()) {
      RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
      rclcpp::shutdown();
    }

    auto head_goal = FollowJointTrajectory::Goal();
    head_goal.trajectory.joint_names.push_back(head_joint_names[0]);
    head_goal.trajectory.joint_names.push_back(head_joint_names[1]);

    //positions
    head_goal.trajectory.points.resize(1);
    head_goal.trajectory.points[0].positions.resize(2);
    head_goal.trajectory.points[0].positions[0] = 0.0;
    head_goal.trajectory.points[0].positions[1] = headAdjustingValue;

    // Velocities
    head_goal.trajectory.points[0].velocities.resize(2);
    for (int j = 0; j < 2; ++j)
    {
        head_goal.trajectory.points[0].velocities[j] = 1.0;
    }
    
    head_goal.trajectory.points[0].time_from_start = rclcpp::Duration(std::chrono::milliseconds(2000));
    
    RCLCPP_INFO(this->get_logger(), "Sending goal");

    auto send_goal_options = rclcpp_action::Client<FollowJointTrajectory>::SendGoalOptions();
    send_goal_options.goal_response_callback =
      std::bind(&TiagoColourFinder::goal_response_callback, this, _1);
    send_goal_options.feedback_callback =
      std::bind(&TiagoColourFinder::feedback_callback, this, _1, _2);
    send_goal_options.result_callback =
      std::bind(&TiagoColourFinder::result_callback, this, _1);
    this->client_ptr_->async_send_goal(head_goal, send_goal_options);
  }

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
      forwardValue = (480 - msg.y)/300;
    }

    if(msg.y > 300){
      float a = msg.y - 240;
      float b = a/240;
      float d = 1.0472 * b;
      float e = (d * (-1.0)); //need this to be negative 
      headAdjustingValue = e;
    }

    if(finished){
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
      finished = false;
      headAdjustingValue = 0.0;
    }
  }
 
  //Declaration of private fields used for timer, publisher and subscriber
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::TimerBase::SharedPtr head_timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  rclcpp::Subscription<geometry_msgs::msg::Point32>::SharedPtr subscription_;

  std::shared_ptr<tf2_ros::TransformListener> tf_listener_{nullptr};
  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
  //std::string target_frame_;

  rclcpp_action::Client<FollowJointTrajectory>::SharedPtr client_ptr_;
  std::string head_joint_names[2] = {"head_1_joint", "head_2_joint"};
  int i=0;

  void goal_response_callback(const GoalHandleFJT::SharedPtr & goal_handle)
  {
    if (!goal_handle) {
      RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
    } else {
      RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
    }
  }
    
  void feedback_callback(
    GoalHandleFJT::SharedPtr,
    const std::shared_ptr<const FollowJointTrajectory::Feedback> feedback)
  {
    std::stringstream ss;
    ss << "Goal feedback current position: " << feedback->actual.positions[0] << ", " << feedback->actual.positions[1] ;
    // ss << "Next number in sequence received: ";
    // for (auto number : feedback->partial_sequence) ;
    //   ss << number << " ";
    // }
    //RCLCPP_INFO(this->get_logger(), ss.str().c_str());
  }

  void result_callback(const GoalHandleFJT::WrappedResult & result)
  {
    switch (result.code) {
      case rclcpp_action::ResultCode::SUCCEEDED:
        break;
      case rclcpp_action::ResultCode::ABORTED:
        RCLCPP_ERROR_STREAM(this->get_logger(), "Goal was aborted: " << result.result->error_string);
        return;
      case rclcpp_action::ResultCode::CANCELED:
        RCLCPP_ERROR_STREAM(this->get_logger(), "Goal was canceled: " << result.result->error_string);
        return;
      default:
        RCLCPP_ERROR_STREAM(this->get_logger(), "Unknown result code: " << result.result->error_string);
        return;
    }
    std::stringstream ss;
    ss << "Goal complete successfully!";
  }
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
