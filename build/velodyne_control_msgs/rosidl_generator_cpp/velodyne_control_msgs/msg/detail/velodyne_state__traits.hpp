// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from velodyne_control_msgs:msg/VelodyneState.idl
// generated code does not contain a copyright notice

#ifndef VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__TRAITS_HPP_
#define VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "velodyne_control_msgs/msg/detail/velodyne_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace velodyne_control_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const VelodyneState & msg,
  std::ostream & out)
{
  out << "{";
  // member: velocity
  {
    out << "velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity, out);
    out << ", ";
  }

  // member: enabled
  {
    out << "enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.enabled, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VelodyneState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity, out);
    out << "\n";
  }

  // member: enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.enabled, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VelodyneState & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace velodyne_control_msgs

namespace rosidl_generator_traits
{

[[deprecated("use velodyne_control_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const velodyne_control_msgs::msg::VelodyneState & msg,
  std::ostream & out, size_t indentation = 0)
{
  velodyne_control_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use velodyne_control_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const velodyne_control_msgs::msg::VelodyneState & msg)
{
  return velodyne_control_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<velodyne_control_msgs::msg::VelodyneState>()
{
  return "velodyne_control_msgs::msg::VelodyneState";
}

template<>
inline const char * name<velodyne_control_msgs::msg::VelodyneState>()
{
  return "velodyne_control_msgs/msg/VelodyneState";
}

template<>
struct has_fixed_size<velodyne_control_msgs::msg::VelodyneState>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<velodyne_control_msgs::msg::VelodyneState>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<velodyne_control_msgs::msg::VelodyneState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__TRAITS_HPP_
