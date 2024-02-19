// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from velodyne_control_msgs:msg/VelodyneState.idl
// generated code does not contain a copyright notice
#include "velodyne_control_msgs/msg/detail/velodyne_state__rosidl_typesupport_fastrtps_cpp.hpp"
#include "velodyne_control_msgs/msg/detail/velodyne_state__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace velodyne_control_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_velodyne_control_msgs
cdr_serialize(
  const velodyne_control_msgs::msg::VelodyneState & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: velocity
  cdr << ros_message.velocity;
  // Member: enabled
  cdr << (ros_message.enabled ? true : false);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_velodyne_control_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  velodyne_control_msgs::msg::VelodyneState & ros_message)
{
  // Member: velocity
  cdr >> ros_message.velocity;

  // Member: enabled
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.enabled = tmp ? true : false;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_velodyne_control_msgs
get_serialized_size(
  const velodyne_control_msgs::msg::VelodyneState & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: velocity
  {
    size_t item_size = sizeof(ros_message.velocity);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: enabled
  {
    size_t item_size = sizeof(ros_message.enabled);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_velodyne_control_msgs
max_serialized_size_VelodyneState(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: velocity
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: enabled
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = velodyne_control_msgs::msg::VelodyneState;
    is_plain =
      (
      offsetof(DataType, enabled) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _VelodyneState__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const velodyne_control_msgs::msg::VelodyneState *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _VelodyneState__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<velodyne_control_msgs::msg::VelodyneState *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _VelodyneState__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const velodyne_control_msgs::msg::VelodyneState *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _VelodyneState__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_VelodyneState(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _VelodyneState__callbacks = {
  "velodyne_control_msgs::msg",
  "VelodyneState",
  _VelodyneState__cdr_serialize,
  _VelodyneState__cdr_deserialize,
  _VelodyneState__get_serialized_size,
  _VelodyneState__max_serialized_size
};

static rosidl_message_type_support_t _VelodyneState__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_VelodyneState__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace velodyne_control_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_velodyne_control_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<velodyne_control_msgs::msg::VelodyneState>()
{
  return &velodyne_control_msgs::msg::typesupport_fastrtps_cpp::_VelodyneState__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, velodyne_control_msgs, msg, VelodyneState)() {
  return &velodyne_control_msgs::msg::typesupport_fastrtps_cpp::_VelodyneState__handle;
}

#ifdef __cplusplus
}
#endif
