// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from velodyne_control_msgs:srv/VelodyneControl.idl
// generated code does not contain a copyright notice

#ifndef VELODYNE_CONTROL_MSGS__SRV__DETAIL__VELODYNE_CONTROL__TRAITS_HPP_
#define VELODYNE_CONTROL_MSGS__SRV__DETAIL__VELODYNE_CONTROL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "velodyne_control_msgs/srv/detail/velodyne_control__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace velodyne_control_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const VelodyneControl_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: velocity
  {
    out << "velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VelodyneControl_Request & msg,
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VelodyneControl_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace velodyne_control_msgs

namespace rosidl_generator_traits
{

[[deprecated("use velodyne_control_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const velodyne_control_msgs::srv::VelodyneControl_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  velodyne_control_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use velodyne_control_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const velodyne_control_msgs::srv::VelodyneControl_Request & msg)
{
  return velodyne_control_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<velodyne_control_msgs::srv::VelodyneControl_Request>()
{
  return "velodyne_control_msgs::srv::VelodyneControl_Request";
}

template<>
inline const char * name<velodyne_control_msgs::srv::VelodyneControl_Request>()
{
  return "velodyne_control_msgs/srv/VelodyneControl_Request";
}

template<>
struct has_fixed_size<velodyne_control_msgs::srv::VelodyneControl_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<velodyne_control_msgs::srv::VelodyneControl_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<velodyne_control_msgs::srv::VelodyneControl_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace velodyne_control_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const VelodyneControl_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VelodyneControl_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VelodyneControl_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace velodyne_control_msgs

namespace rosidl_generator_traits
{

[[deprecated("use velodyne_control_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const velodyne_control_msgs::srv::VelodyneControl_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  velodyne_control_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use velodyne_control_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const velodyne_control_msgs::srv::VelodyneControl_Response & msg)
{
  return velodyne_control_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<velodyne_control_msgs::srv::VelodyneControl_Response>()
{
  return "velodyne_control_msgs::srv::VelodyneControl_Response";
}

template<>
inline const char * name<velodyne_control_msgs::srv::VelodyneControl_Response>()
{
  return "velodyne_control_msgs/srv/VelodyneControl_Response";
}

template<>
struct has_fixed_size<velodyne_control_msgs::srv::VelodyneControl_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<velodyne_control_msgs::srv::VelodyneControl_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<velodyne_control_msgs::srv::VelodyneControl_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<velodyne_control_msgs::srv::VelodyneControl>()
{
  return "velodyne_control_msgs::srv::VelodyneControl";
}

template<>
inline const char * name<velodyne_control_msgs::srv::VelodyneControl>()
{
  return "velodyne_control_msgs/srv/VelodyneControl";
}

template<>
struct has_fixed_size<velodyne_control_msgs::srv::VelodyneControl>
  : std::integral_constant<
    bool,
    has_fixed_size<velodyne_control_msgs::srv::VelodyneControl_Request>::value &&
    has_fixed_size<velodyne_control_msgs::srv::VelodyneControl_Response>::value
  >
{
};

template<>
struct has_bounded_size<velodyne_control_msgs::srv::VelodyneControl>
  : std::integral_constant<
    bool,
    has_bounded_size<velodyne_control_msgs::srv::VelodyneControl_Request>::value &&
    has_bounded_size<velodyne_control_msgs::srv::VelodyneControl_Response>::value
  >
{
};

template<>
struct is_service<velodyne_control_msgs::srv::VelodyneControl>
  : std::true_type
{
};

template<>
struct is_service_request<velodyne_control_msgs::srv::VelodyneControl_Request>
  : std::true_type
{
};

template<>
struct is_service_response<velodyne_control_msgs::srv::VelodyneControl_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // VELODYNE_CONTROL_MSGS__SRV__DETAIL__VELODYNE_CONTROL__TRAITS_HPP_
