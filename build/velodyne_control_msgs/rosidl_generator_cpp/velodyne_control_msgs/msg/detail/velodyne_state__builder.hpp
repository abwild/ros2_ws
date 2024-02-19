// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from velodyne_control_msgs:msg/VelodyneState.idl
// generated code does not contain a copyright notice

#ifndef VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__BUILDER_HPP_
#define VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "velodyne_control_msgs/msg/detail/velodyne_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace velodyne_control_msgs
{

namespace msg
{

namespace builder
{

class Init_VelodyneState_enabled
{
public:
  explicit Init_VelodyneState_enabled(::velodyne_control_msgs::msg::VelodyneState & msg)
  : msg_(msg)
  {}
  ::velodyne_control_msgs::msg::VelodyneState enabled(::velodyne_control_msgs::msg::VelodyneState::_enabled_type arg)
  {
    msg_.enabled = std::move(arg);
    return std::move(msg_);
  }

private:
  ::velodyne_control_msgs::msg::VelodyneState msg_;
};

class Init_VelodyneState_velocity
{
public:
  Init_VelodyneState_velocity()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VelodyneState_enabled velocity(::velodyne_control_msgs::msg::VelodyneState::_velocity_type arg)
  {
    msg_.velocity = std::move(arg);
    return Init_VelodyneState_enabled(msg_);
  }

private:
  ::velodyne_control_msgs::msg::VelodyneState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::velodyne_control_msgs::msg::VelodyneState>()
{
  return velodyne_control_msgs::msg::builder::Init_VelodyneState_velocity();
}

}  // namespace velodyne_control_msgs

#endif  // VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__BUILDER_HPP_
