// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from velodyne_control_msgs:msg/VelodyneState.idl
// generated code does not contain a copyright notice

#ifndef VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__FUNCTIONS_H_
#define VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "velodyne_control_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "velodyne_control_msgs/msg/detail/velodyne_state__struct.h"

/// Initialize msg/VelodyneState message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * velodyne_control_msgs__msg__VelodyneState
 * )) before or use
 * velodyne_control_msgs__msg__VelodyneState__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_velodyne_control_msgs
bool
velodyne_control_msgs__msg__VelodyneState__init(velodyne_control_msgs__msg__VelodyneState * msg);

/// Finalize msg/VelodyneState message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_velodyne_control_msgs
void
velodyne_control_msgs__msg__VelodyneState__fini(velodyne_control_msgs__msg__VelodyneState * msg);

/// Create msg/VelodyneState message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * velodyne_control_msgs__msg__VelodyneState__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_velodyne_control_msgs
velodyne_control_msgs__msg__VelodyneState *
velodyne_control_msgs__msg__VelodyneState__create();

/// Destroy msg/VelodyneState message.
/**
 * It calls
 * velodyne_control_msgs__msg__VelodyneState__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_velodyne_control_msgs
void
velodyne_control_msgs__msg__VelodyneState__destroy(velodyne_control_msgs__msg__VelodyneState * msg);

/// Check for msg/VelodyneState message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_velodyne_control_msgs
bool
velodyne_control_msgs__msg__VelodyneState__are_equal(const velodyne_control_msgs__msg__VelodyneState * lhs, const velodyne_control_msgs__msg__VelodyneState * rhs);

/// Copy a msg/VelodyneState message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_velodyne_control_msgs
bool
velodyne_control_msgs__msg__VelodyneState__copy(
  const velodyne_control_msgs__msg__VelodyneState * input,
  velodyne_control_msgs__msg__VelodyneState * output);

/// Initialize array of msg/VelodyneState messages.
/**
 * It allocates the memory for the number of elements and calls
 * velodyne_control_msgs__msg__VelodyneState__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_velodyne_control_msgs
bool
velodyne_control_msgs__msg__VelodyneState__Sequence__init(velodyne_control_msgs__msg__VelodyneState__Sequence * array, size_t size);

/// Finalize array of msg/VelodyneState messages.
/**
 * It calls
 * velodyne_control_msgs__msg__VelodyneState__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_velodyne_control_msgs
void
velodyne_control_msgs__msg__VelodyneState__Sequence__fini(velodyne_control_msgs__msg__VelodyneState__Sequence * array);

/// Create array of msg/VelodyneState messages.
/**
 * It allocates the memory for the array and calls
 * velodyne_control_msgs__msg__VelodyneState__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_velodyne_control_msgs
velodyne_control_msgs__msg__VelodyneState__Sequence *
velodyne_control_msgs__msg__VelodyneState__Sequence__create(size_t size);

/// Destroy array of msg/VelodyneState messages.
/**
 * It calls
 * velodyne_control_msgs__msg__VelodyneState__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_velodyne_control_msgs
void
velodyne_control_msgs__msg__VelodyneState__Sequence__destroy(velodyne_control_msgs__msg__VelodyneState__Sequence * array);

/// Check for msg/VelodyneState message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_velodyne_control_msgs
bool
velodyne_control_msgs__msg__VelodyneState__Sequence__are_equal(const velodyne_control_msgs__msg__VelodyneState__Sequence * lhs, const velodyne_control_msgs__msg__VelodyneState__Sequence * rhs);

/// Copy an array of msg/VelodyneState messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_velodyne_control_msgs
bool
velodyne_control_msgs__msg__VelodyneState__Sequence__copy(
  const velodyne_control_msgs__msg__VelodyneState__Sequence * input,
  velodyne_control_msgs__msg__VelodyneState__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__FUNCTIONS_H_
