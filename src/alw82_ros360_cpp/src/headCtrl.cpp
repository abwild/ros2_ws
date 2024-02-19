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

class HeadCtrl : public rclcpp::Node
{
    using FollowJointTrajectory = control_msgs::action::FollowJointTrajectory;
    using GoalHandleFJT = rclcpp_action::ClientGoalHandle<FollowJointTrajectory>;
    public:
        HeadCtrl() : Node("headController")
        {
            this->client_ptr_ = rclcpp_action::create_client<FollowJointTrajectory>(
                this,
                "head_controller/follow_joint_trajectory");

            this->timer_ = this->create_wall_timer(
                std::chrono::milliseconds(10000),
                std::bind(&HeadCtrl::send_goal, this));

        }

        void send_goal()
        {
            using namespace std::placeholders;

            //this->timer_->cancel();

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
            head_goal.trajectory.points[0].positions[0] = head_joint_positions[i][0];
            head_goal.trajectory.points[0].positions[1] = head_joint_positions[i][1];

            
            // Velocities
            head_goal.trajectory.points[0].velocities.resize(2);
            for (int j = 0; j < 2; ++j)
            {
               head_goal.trajectory.points[0].velocities[j] = 1.0;
            }
            
            head_goal.trajectory.points[0].time_from_start = rclcpp::Duration(std::chrono::milliseconds(2000));
            //head_goal.trajectory.header.stamp = this->get_clock()->now() + rclcpp::Duration(std::chrono::milliseconds(100));

            

            RCLCPP_INFO(this->get_logger(), "Sending goal");

            auto send_goal_options = rclcpp_action::Client<FollowJointTrajectory>::SendGoalOptions();
            send_goal_options.goal_response_callback =
              std::bind(&HeadCtrl::goal_response_callback, this, _1);
            send_goal_options.feedback_callback =
              std::bind(&HeadCtrl::feedback_callback, this, _1, _2);
            send_goal_options.result_callback =
              std::bind(&HeadCtrl::result_callback, this, _1);
            this->client_ptr_->async_send_goal(head_goal, send_goal_options);

            i++;
            i%=3;
        }

    private:
        rclcpp_action::Client<FollowJointTrajectory>::SharedPtr client_ptr_;
        rclcpp::TimerBase::SharedPtr timer_;
        std::string head_joint_names[2] = {"head_1_joint", "head_2_joint"};
        int i=0;
        float head_joint_positions[3][2] = {  
            {-1.309, -1.0472} , 
            {1.309, 0.785398} ,
            {0.0, 0.0}
        };

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

    rclcpp::spin(std::make_shared<HeadCtrl>());

    rclcpp::shutdown();
    return 0;

}