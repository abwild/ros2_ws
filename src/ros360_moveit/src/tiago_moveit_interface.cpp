#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/msg/collision_object.hpp>

#include "std_msgs/msg/bool.hpp"
#include <geometry_msgs/msg/pose.hpp>

using namespace std::chrono_literals;
using std::placeholders::_1;

// Joint control group from the robot specification
static const std::string PLANNING_GROUP = "arm_torso";

class TiagoMoveitInterface : public rclcpp::Node//, std::enable_shared_from_this<TiagoMoveitInterface>
{
  public:
    TiagoMoveitInterface(rclcpp::NodeOptions options) : Node("tiago_moveit_interface", options)
    {
      //const rclcpp::Node* my_node = dynamic_cast <rclcpp::Node*> (this);
      
      //const std::shared_ptr<rclcpp::Node>&
      //std::shared_ptr<rclcpp::Node> my_node_ptr(this);
      
      // Create the MoveIt MoveGroup Interface
      //move_group_interface = new moveit::planning_interface::MoveGroupInterface(shared_from_this(), PLANNING_GROUP);
      subscription_ = this->create_subscription<geometry_msgs::msg::Pose>(
      "/ros360_moveit/request", 10, std::bind(&TiagoMoveitInterface::request_callback, this, _1));
    
      publisher_ = this->create_publisher<std_msgs::msg::Bool>("/ros360_moveit/result", 10);


      
    }

    // const std::shared_ptr<rclcpp::Node> getptr() const
    // {
    //   return shared_from_this();
    // }

    void initMoveGroup()//rclcpp::Node::SharedPtr node)
    {
      move_group_interface = new moveit::planning_interface::MoveGroupInterface(shared_from_this(), PLANNING_GROUP);
      addCollisionObjects();
    }

  private:

    void request_callback(const geometry_msgs::msg::Pose & msg)
    {
      RCLCPP_INFO(this->get_logger(), "******** Received Request to move to pose ********");

      // Set a target Pose
      geometry_msgs::msg::Pose target_pose = msg;
      moveit::planning_interface::MoveGroupInterface::Plan my_plan;
      move_group_interface->setPoseTarget(target_pose);

      // Create a plan to that target pose
      bool success = (move_group_interface->plan(my_plan) == moveit::core::MoveItErrorCode::SUCCESS);
      RCLCPP_INFO(this->get_logger(), "Generating plan to target pose 1 %s", success ? "" : "FAILED");

      // Execute the plan
      if(success) {
        move_group_interface->execute(my_plan);
        RCLCPP_INFO(this->get_logger(), "Executing plan succeeded");
      } else {
        RCLCPP_ERROR(this->get_logger(), "Executing planning failed!");
      }

      std_msgs::msg::Bool response = std_msgs::msg::Bool();
      response.data = success;
      publisher_->publish(response);

    }

    void addCollisionObjects(){
      moveit::planning_interface::PlanningSceneInterface planning_scene_interface;

      //Add collision objects into the planning scene
      moveit_msgs::msg::CollisionObject collision_object;
      collision_object.header.frame_id = move_group_interface->getPlanningFrame();

      // The id of the object is used to identify it.
      collision_object.id = "box1";

      // Define a box to add to the world.
      shape_msgs::msg::SolidPrimitive primitive;
      primitive.type = primitive.BOX;
      primitive.dimensions.resize(3);
      primitive.dimensions[primitive.BOX_X] = 0.913;
      primitive.dimensions[primitive.BOX_Y] = 0.913;
      primitive.dimensions[primitive.BOX_Z] = 0.04;

      // Define a pose for the box (specified relative to frame_id).
      geometry_msgs::msg::Pose box_pose;
      box_pose.orientation.w = 1.0;
      box_pose.position.x = 1.0;
      box_pose.position.y = 0.0;
      box_pose.position.z = 0.5;

      collision_object.primitives.push_back(primitive);
      collision_object.primitive_poses.push_back(box_pose);
      collision_object.operation = collision_object.ADD;

      std::vector<moveit_msgs::msg::CollisionObject> collision_objects;
      collision_objects.push_back(collision_object);

      // Now, let's add the collision object into the world
      // (using a vector that could contain additional objects)
      RCLCPP_INFO(this->get_logger(), "Add an object into the world");
      planning_scene_interface.addCollisionObjects(collision_objects);
    }


  
    moveit::planning_interface::MoveGroupInterface* move_group_interface;
    


    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr publisher_;
    rclcpp::Subscription<geometry_msgs::msg::Pose>::SharedPtr subscription_;

};




int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  // Initialize ROS and create the Node
  rclcpp::NodeOptions node_options;
  node_options.automatically_declare_parameters_from_overrides(true);
  
  
  // Instantiate a node.
   std::shared_ptr<TiagoMoveitInterface> node = std::make_shared<TiagoMoveitInterface>(node_options);
   node->initMoveGroup();
  
  // We spin up a SingleThreadedExecutor for the current state monitor to get information
  // about the robot's state.
  // rclcpp::executors::SingleThreadedExecutor executor;
  // executor.add_node(node);
  // std::thread([&executor]() { executor.spin(); });//.detach();
  
  rclcpp::spin(node);


  //******** move to joint configuration
/*
    RCLCPP_INFO(logger, "******** MOVING TO JOINT CONFIGURATION ********");

  const moveit::core::JointModelGroup* joint_model_group =
        move_group_interface.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

  moveit::core::RobotStatePtr current_state = move_group_interface.getCurrentState(100);

  //Obtain the current joint configuration
  std::vector<double> joint_group_positions;
    current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);

  //Set or update a joint position
  joint_group_positions[0] = -1.0;  // radians
  move_group_interface.setJointValueTarget(joint_group_positions);

  success = (move_group_interface.plan(my_plan) == moveit::core::MoveItErrorCode::SUCCESS);
  RCLCPP_INFO(logger, "Visualizing plan 2 (joint space goal) %s", success ? "" : "FAILED");

*/



  // Shutdown ROS
  rclcpp::shutdown();
  return 0;
}