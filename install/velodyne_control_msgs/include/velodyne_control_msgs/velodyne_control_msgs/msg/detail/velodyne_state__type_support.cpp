// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from velodyne_control_msgs:msg/VelodyneState.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "velodyne_control_msgs/msg/detail/velodyne_state__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace velodyne_control_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void VelodyneState_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) velodyne_control_msgs::msg::VelodyneState(_init);
}

void VelodyneState_fini_function(void * message_memory)
{
  auto typed_message = static_cast<velodyne_control_msgs::msg::VelodyneState *>(message_memory);
  typed_message->~VelodyneState();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember VelodyneState_message_member_array[2] = {
  {
    "velocity",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(velodyne_control_msgs::msg::VelodyneState, velocity),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "enabled",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(velodyne_control_msgs::msg::VelodyneState, enabled),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers VelodyneState_message_members = {
  "velodyne_control_msgs::msg",  // message namespace
  "VelodyneState",  // message name
  2,  // number of fields
  sizeof(velodyne_control_msgs::msg::VelodyneState),
  VelodyneState_message_member_array,  // message members
  VelodyneState_init_function,  // function to initialize message memory (memory has to be allocated)
  VelodyneState_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t VelodyneState_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &VelodyneState_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace velodyne_control_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<velodyne_control_msgs::msg::VelodyneState>()
{
  return &::velodyne_control_msgs::msg::rosidl_typesupport_introspection_cpp::VelodyneState_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, velodyne_control_msgs, msg, VelodyneState)() {
  return &::velodyne_control_msgs::msg::rosidl_typesupport_introspection_cpp::VelodyneState_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
