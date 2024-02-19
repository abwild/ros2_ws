// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from velodyne_control_msgs:msg/VelodyneState.idl
// generated code does not contain a copyright notice

#ifndef VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__STRUCT_H_
#define VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/VelodyneState in the package velodyne_control_msgs.
typedef struct velodyne_control_msgs__msg__VelodyneState
{
  /// Velocity for rotation
  double velocity;
  /// {true} if the velocity of rotation can be modified // {false} if the rotation is stopped.
  bool enabled;
} velodyne_control_msgs__msg__VelodyneState;

// Struct for a sequence of velodyne_control_msgs__msg__VelodyneState.
typedef struct velodyne_control_msgs__msg__VelodyneState__Sequence
{
  velodyne_control_msgs__msg__VelodyneState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} velodyne_control_msgs__msg__VelodyneState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__STRUCT_H_
