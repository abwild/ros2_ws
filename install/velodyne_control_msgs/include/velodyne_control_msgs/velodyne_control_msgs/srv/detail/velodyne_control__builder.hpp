// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from velodyne_control_msgs:srv/VelodyneControl.idl
// generated code does not contain a copyright notice

#ifndef VELODYNE_CONTROL_MSGS__SRV__DETAIL__VELODYNE_CONTROL__BUILDER_HPP_
#define VELODYNE_CONTROL_MSGS__SRV__DETAIL__VELODYNE_CONTROL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "velodyne_control_msgs/srv/detail/velodyne_control__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace velodyne_control_msgs
{

namespace srv
{

namespace builder
{

class Init_VelodyneControl_Request_velocity
{
public:
  Init_VelodyneControl_Request_velocity()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::velodyne_control_msgs::srv::VelodyneControl_Request velocity(::velodyne_control_msgs::srv::VelodyneControl_Request::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return std::move(msg_);
  }

private:
  ::velodyne_control_msgs::srv::VelodyneControl_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::velodyne_control_msgs::srv::VelodyneControl_Request>()
{
  return velodyne_control_msgs::srv::builder::Init_VelodyneControl_Request_velocity();
}

}  // namespace velodyne_control_msgs


namespace velodyne_control_msgs
{

namespace srv
{

namespace builder
{

class Init_VelodyneControl_Response_success
{
public:
  Init_VelodyneControl_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::velodyne_control_msgs::srv::VelodyneControl_Response success(::velodyne_control_msgs::srv::VelodyneControl_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::velodyne_control_msgs::srv::VelodyneControl_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::velodyne_control_msgs::srv::VelodyneControl_Response>()
{
  return velodyne_control_msgs::srv::builder::Init_VelodyneControl_Response_success();
}

}  // namespace velodyne_control_msgs

#endif  // VELODYNE_CONTROL_MSGS__SRV__DETAIL__VELODYNE_CONTROL__BUILDER_HPP_
