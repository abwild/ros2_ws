// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from velodyne_control_msgs:srv/VelodyneControl.idl
// generated code does not contain a copyright notice

#ifndef VELODYNE_CONTROL_MSGS__SRV__DETAIL__VELODYNE_CONTROL__STRUCT_H_
#define VELODYNE_CONTROL_MSGS__SRV__DETAIL__VELODYNE_CONTROL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/VelodyneControl in the package velodyne_control_msgs.
typedef struct velodyne_control_msgs__srv__VelodyneControl_Request
{
  /// Desired velocity of rotation for velodyne.
  double velocity;
} velodyne_control_msgs__srv__VelodyneControl_Request;

// Struct for a sequence of velodyne_control_msgs__srv__VelodyneControl_Request.
typedef struct velodyne_control_msgs__srv__VelodyneControl_Request__Sequence
{
  velodyne_control_msgs__srv__VelodyneControl_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} velodyne_control_msgs__srv__VelodyneControl_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/VelodyneControl in the package velodyne_control_msgs.
typedef struct velodyne_control_msgs__srv__VelodyneControl_Response
{
  /// RESULT: SUCCESS message.
  bool success;
} velodyne_control_msgs__srv__VelodyneControl_Response;

// Struct for a sequence of velodyne_control_msgs__srv__VelodyneControl_Response.
typedef struct velodyne_control_msgs__srv__VelodyneControl_Response__Sequence
{
  velodyne_control_msgs__srv__VelodyneControl_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} velodyne_control_msgs__srv__VelodyneControl_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VELODYNE_CONTROL_MSGS__SRV__DETAIL__VELODYNE_CONTROL__STRUCT_H_
