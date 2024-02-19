#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <future>
#include <sstream>

#include <stdlib.h>

#include <math.h>

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"
#include "control_msgs/action/follow_joint_trajectory.hpp"
#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"

#include "std_msgs/msg/string.hpp" 
#include "std_msgs/msg/bool.hpp"
#include "geometry_msgs/msg/twist.hpp" 
#include "geometry_msgs/msg/point32.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"

#include "tf2/exceptions.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"

using namespace std::chrono_literals;
using namespace std::placeholders;


class Alw82Assignment : public rclcpp::Node
{
using FollowJointTrajectory = control_msgs::action::FollowJointTrajectory;
using GoalHandleFJT = rclcpp_action::ClientGoalHandle<FollowJointTrajectory>;
public:

  /* values to track the state in the robot fsm */
  enum robot_state {FOLLOWING, SEARCHING, GRASPING, DELIVERING, REPOSITIONING};
  robot_state state;

  /* values for following the walls */
  float leftVals [40];
  float rightVals [40];
  float centVals [40];
  float leftTotal = 0;
  float rightTotal = 0;
  float centTotal = 0;

  /* values for detecting different colours */
  long int ranges_b[3] = {255,10,10};
  long int ranges_g[3] = {9,255,8};
  long int ranges_r[3] = {0,0,255};

  /* values for moving towards the cubes */
  float adjustingValue;
  float forwardValue;
  float headAdjustingValue = 0.0;
  bool foundSomething = false;
  bool closeEnough = false;
  float distanceToCube;

  int move_success = 0; /* used for waiting until arm move finished */

  float tf_x;
  float tf_y;
  float tf_z;
  
  Alw82Assignment() : Node("alw82_assignment")
  {
    twist_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/servoing_cmd_vel", 10);

    arm_publisher_ = this->create_publisher<geometry_msgs::msg::Pose>("/ros360_moveit/request", 10);

    laser_subscription_ = this->create_subscription<sensor_msgs::msg::LaserScan>(
      "/scan_raw", 10, std::bind(&Alw82Assignment::laser_callback, this, _1));

    colour_subscription_ = this->create_subscription<geometry_msgs::msg::Point32>(
      "/colour_detection", 10, std::bind(&Alw82Assignment::colour_callback_, this, _1));

    arm_subscription_ = this->create_subscription<std_msgs::msg::Bool>(
      "ros360_moveit/result", 10, std::bind(&Alw82Assignment::arm_moveit_callback, this, _1));

    state_timer_ = this->create_wall_timer(
      100ms, std::bind(&Alw82Assignment::state_timer_callback, this));

    tf_timer_ = this->create_wall_timer(
      100ms, std::bind(&Alw82Assignment::tf_timer_callback, this));

    tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());

    tf_listener_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);

    this->head_client_ptr_ = rclcpp_action::create_client<FollowJointTrajectory>(this, "head_controller/follow_joint_trajectory");

    head_timer_ = this->create_wall_timer(2000ms, std::bind(&Alw82Assignment::head_timer, this));

    send_request(ranges_b);
  }
  

private:

  void state_timer_callback()
  {
    RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 500, 
    		 "State: %d", state);

    RCLCPP_INFO_THROTTLE(this->get_logger(),
    		 *this->get_clock(), 
    		 500, 
    		 "Move_success: %d", move_success);
    auto message_t = geometry_msgs::msg::Twist();
    auto message_p = geometry_msgs::msg::Pose();
    float difference = 0.0;
    switch(state){ /* checking the state each timer to respond as necessary */
      case FOLLOWING:
        difference = leftTotal - rightTotal;
        message_t.angular.z = difference * 0.9;
        message_t.linear.x = (centTotal/10)*4.0;
        break;
      case SEARCHING:
        send_request(ranges_b);
        if(!foundSomething){ /* move towards object until we find it */
            message_t.linear.x = 1.0;
            message_t.angular.z = difference * 0.9;
        }else{
            message_t.angular.z = adjustingValue;
            message_t.linear.x = forwardValue;
        }
        break;
      case GRASPING:
      /* transform z is off by about 0.11 so increase it by 1.1 before offset */
        if(move_success == 0){ /* value changes from ros360_moveit/result callback */
          message_t.linear.x = 0.0;
          message_p.position.x = 0.576;
          message_p.position.y = -0.594;
          message_p.position.z = 0.854;
          arm_publisher_->publish(message_p);
        }
        if(move_success == 1 && (distanceToCube > 0.6)){
          message_t.linear.x = 0.1;
        }if(move_success == 1 && distanceToCube < 0.6){
          message_p.position.x = tf_x;
          message_p.position.y = tf_y;
          message_p.position.z = tf_z;
          arm_publisher_->publish(message_p);
          /* grasp cube */
        }
        if(move_success == 2){ /* if the arm has moved twice */
          move_success = 0; /* reset for the next cube */
          foundSomething = false; /* reset so we search for the bin */
          state = DELIVERING;
        }
        break;
      case DELIVERING:
        send_request(ranges_g);
        headAdjustingValue = -1;
        if(!foundSomething){
          message_t.angular.z = -0.5; /* rotate until we find bin*/
        }
        if(foundSomething){
          message_t.angular.z = adjustingValue;
          message_t.linear.x = forwardValue;
          if(tf_x >= 0.25){
            /* release gripper */
            send_request(ranges_b);
            foundSomething = false;
            state = REPOSITIONING;
          }
        }
        break;
      case REPOSITIONING:
        send_request(ranges_b);
        if(foundSomething){
          state = GRASPING;
        }else{
          message_t.angular.z = -0.5;
        }
        break;
      default:
        break;
    }
    
    twist_publisher_->publish(message_t);
  }

  /* timer to check the tf tree */
  void tf_timer_callback(){
    std::string fromFrame = "target_object";
    std::string toFrame = "base_link";

    geometry_msgs::msg::TransformStamped t;

    try{
        t = tf_buffer_->lookupTransform(toFrame, fromFrame, tf2::TimePointZero);
        if(t.transform.translation.x <= 1.50){
            closeEnough = true;
        }
        distanceToCube = t.transform.translation.x;
        tf_x = t.transform.translation.x;
        tf_y = t.transform.translation.y;
        tf_z = t.transform.translation.z;
    } catch (const tf2::TransformException & ex){
        RCLCPP_INFO(this->get_logger(), "Could not find transform");
        return;
    }
  }

  void laser_callback(const sensor_msgs::msg::LaserScan & msg)
  {
    /* getting the sensor values */
    for(int i=86; i>46; i--){
    	if(!isinf(msg.ranges[i])){
    		rightVals[86-i] = msg.ranges[i];
    	}
    }
    for(int i=620; i>580; i--){
    	if(!isinf(msg.ranges[i])){
    		leftVals[620-i] = msg.ranges[i];
    	}
    }
    for(int i=340; i>300; i--){
    	if(!isinf(msg.ranges[i])){
    		centVals[340-i] = msg.ranges[i];
    	}
    }
    /* averaging the values to account for noise */
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

    /* check if left and right values are high enough to assume out of corridor then 
      change state*/
    if(leftTotal > 5 && rightTotal > 5 && state == FOLLOWING){
        state = SEARCHING;
    }
  }

  void head_timer()
  {
    using namespace std::placeholders;

    if (!this->head_client_ptr_->wait_for_action_server()) {
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
      std::bind(&Alw82Assignment::goal_response_callback, this, _1);
    send_goal_options.feedback_callback =
      std::bind(&Alw82Assignment::feedback_callback, this, _1, _2);
    send_goal_options.result_callback =
      std::bind(&Alw82Assignment::result_callback, this, _1);
    this->head_client_ptr_->async_send_goal(head_goal, send_goal_options);
  }

  void arm_moveit_callback(const std_msgs::msg::Bool & msg)
  {
    if(msg.data == true){
      move_success++;
    }
  }

  void colour_callback_(const geometry_msgs::msg::Point32 & msg) 
  {
    if(!closeEnough){
        foundSomething = true; /* we have an object as soon as something publishes to this topic */
        /* calculate how to move to centre the object detected */
        if(msg.x != 320){
            adjustingValue = (320 - msg.x)/200;
        }else{
            adjustingValue = 0.0;
        }
        /* clamping to prevent the robot turning too fast/much */
        if(adjustingValue > 1.0){
            adjustingValue = 1.0;
        }else if(adjustingValue < -1.0){
            adjustingValue = -1.0;
        }
        /* if we are suitably centred start moving towards the object */
        if((adjustingValue <= 0.1 && adjustingValue > 0)
        || (adjustingValue < 0 && adjustingValue >= -0.1)){
            forwardValue = (480 - msg.y)/300;
        }
        /* calculating how much to tilt the head by */
        if(msg.y > 300){
            float a = msg.y - 240;
            float b = a/240;
            float d = 1.0472 * b;
            float e = (d * (-1.0));
            headAdjustingValue = e;
        }
    }
    /* transform listener sets close enough when within range */
    if(closeEnough && state == SEARCHING){
        adjustingValue = 0.0;
        forwardValue = 0.0;
        state = GRASPING; /* begin grasping once we are within range */
    }
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
 
  rclcpp::TimerBase::SharedPtr state_timer_;
  rclcpp::TimerBase::SharedPtr head_timer_;
  rclcpp::TimerBase::SharedPtr tf_timer_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_publisher_;
  rclcpp::Publisher<geometry_msgs::msg::Pose>::SharedPtr arm_publisher_;
  rclcpp::Subscription<geometry_msgs::msg::Point32>::SharedPtr colour_subscription_;
  rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr laser_subscription_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr arm_subscription_;

  std::shared_ptr<tf2_ros::TransformListener> tf_listener_{nullptr};
  std::unique_ptr<tf2_ros::Buffer> tf_buffer_;

  rclcpp_action::Client<FollowJointTrajectory>::SharedPtr head_client_ptr_;

  std::string head_joint_names[2] = {"head_1_joint", "head_2_joint"};

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

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  rclcpp::spin(std::make_shared<Alw82Assignment>());

  rclcpp::shutdown();
  return 0;
}
