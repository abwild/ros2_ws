#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>

#include "control_msgs/action/follow_joint_trajectory.hpp"
#include "trajectory_msgs/msg/joint_trajectory.hpp"
#include "trajectory_msgs/msg/joint_trajectory_point.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"

class TorsoCtrl : public rclcpp::Node
{
    using FollowJointTrajectory = control_msgs::action::FollowJointTrajectory;
    using GoalHandleFJT = rclcpp_action::ClientGoalHandle<FollowJointTrajectory>;
    public:
        TorsoCtrl() : Node("torsoController")
        {
            this->client_ptr_ = rclcpp_action::create_client<FollowJointTrajectory>(
                this,
                "torso_controller/follow_joint_trajectory");

            this->timer_ = this->create_wall_timer(
                std::chrono::milliseconds(10000),
                std::bind(&TorsoCtrl::send_goal, this));

        }

        void send_goal()
        {
            using namespace std::placeholders;

            //this->timer_->cancel();

            if (!this->client_ptr_->wait_for_action_server()) {
              RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
              rclcpp::shutdown();
            }

            auto torso_goal = FollowJointTrajectory::Goal();
            torso_goal.trajectory.joint_names.push_back(torso_joint_names[0]);

            //positions
            torso_goal.trajectory.points.resize(1);
            torso_goal.trajectory.points[0].positions.resize(1);
            torso_goal.trajectory.points[0].positions[0] = torso_joint_positions[i];

            
            // Velocities
            torso_goal.trajectory.points[0].velocities.resize(1);
            torso_goal.trajectory.points[0].velocities[0] = 1.0;
            
            torso_goal.trajectory.points[0].time_from_start = rclcpp::Duration(std::chrono::milliseconds(2000));
            //torso_goal.trajectory.header.stamp = this->get_clock()->now() + rclcpp::Duration(std::chrono::milliseconds(100));

            

            RCLCPP_INFO(this->get_logger(), "Sending goal");

            auto send_goal_options = rclcpp_action::Client<FollowJointTrajectory>::SendGoalOptions();
            send_goal_options.goal_response_callback =
              std::bind(&TorsoCtrl::goal_response_callback, this, _1);
            send_goal_options.feedback_callback =
              std::bind(&TorsoCtrl::feedback_callback, this, _1, _2);
            send_goal_options.result_callback =
              std::bind(&TorsoCtrl::result_callback, this, _1);
            this->client_ptr_->async_send_goal(torso_goal, send_goal_options);

            i++;
            i%=2;
        }

    private:
        rclcpp_action::Client<FollowJointTrajectory>::SharedPtr client_ptr_;
        rclcpp::TimerBase::SharedPtr timer_;
        std::string torso_joint_names[1] = {"torso_lift_joint"};
        int i=0;
        float torso_joint_positions[2] = {0.0, 0.35};

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
            RCLCPP_INFO(this->get_logger(), ss.str().c_str());
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
            // for (auto number : result.result->sequence) {
            //   ss << number << " ";
            // }
            RCLCPP_INFO(this->get_logger(), ss.str().c_str());
            //rclcpp::shutdown();
        }



};


int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<TorsoCtrl>());

    rclcpp::shutdown();
    return 0;

}