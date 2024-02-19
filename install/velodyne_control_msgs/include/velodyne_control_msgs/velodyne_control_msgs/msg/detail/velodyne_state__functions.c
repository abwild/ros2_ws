// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from velodyne_control_msgs:msg/VelodyneState.idl
// generated code does not contain a copyright notice
#include "velodyne_control_msgs/msg/detail/velodyne_state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
velodyne_control_msgs__msg__VelodyneState__init(velodyne_control_msgs__msg__VelodyneState * msg)
{
  if (!msg) {
    return false;
  }
  // velocity
  // enabled
  return true;
}

void
velodyne_control_msgs__msg__VelodyneState__fini(velodyne_control_msgs__msg__VelodyneState * msg)
{
  if (!msg) {
    return;
  }
  // velocity
  // enabled
}

bool
velodyne_control_msgs__msg__VelodyneState__are_equal(const velodyne_control_msgs__msg__VelodyneState * lhs, const velodyne_control_msgs__msg__VelodyneState * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // velocity
  if (lhs->velocity != rhs->velocity) {
    return false;
  }
  // enabled
  if (lhs->enabled != rhs->enabled) {
    return false;
  }
  return true;
}

bool
velodyne_control_msgs__msg__VelodyneState__copy(
  const velodyne_control_msgs__msg__VelodyneState * input,
  velodyne_control_msgs__msg__VelodyneState * output)
{
  if (!input || !output) {
    return false;
  }
  // velocity
  output->velocity = input->velocity;
  // enabled
  output->enabled = input->enabled;
  return true;
}

velodyne_control_msgs__msg__VelodyneState *
velodyne_control_msgs__msg__VelodyneState__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  velodyne_control_msgs__msg__VelodyneState * msg = (velodyne_control_msgs__msg__VelodyneState *)allocator.allocate(sizeof(velodyne_control_msgs__msg__VelodyneState), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(velodyne_control_msgs__msg__VelodyneState));
  bool success = velodyne_control_msgs__msg__VelodyneState__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
velodyne_control_msgs__msg__VelodyneState__destroy(velodyne_control_msgs__msg__VelodyneState * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    velodyne_control_msgs__msg__VelodyneState__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
velodyne_control_msgs__msg__VelodyneState__Sequence__init(velodyne_control_msgs__msg__VelodyneState__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  velodyne_control_msgs__msg__VelodyneState * data = NULL;

  if (size) {
    data = (velodyne_control_msgs__msg__VelodyneState *)allocator.zero_allocate(size, sizeof(velodyne_control_msgs__msg__VelodyneState), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = velodyne_control_msgs__msg__VelodyneState__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        velodyne_control_msgs__msg__VelodyneState__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
velodyne_control_msgs__msg__VelodyneState__Sequence__fini(velodyne_control_msgs__msg__VelodyneState__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      velodyne_control_msgs__msg__VelodyneState__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

velodyne_control_msgs__msg__VelodyneState__Sequence *
velodyne_control_msgs__msg__VelodyneState__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  velodyne_control_msgs__msg__VelodyneState__Sequence * array = (velodyne_control_msgs__msg__VelodyneState__Sequence *)allocator.allocate(sizeof(velodyne_control_msgs__msg__VelodyneState__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = velodyne_control_msgs__msg__VelodyneState__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
velodyne_control_msgs__msg__VelodyneState__Sequence__destroy(velodyne_control_msgs__msg__VelodyneState__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    velodyne_control_msgs__msg__VelodyneState__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
velodyne_control_msgs__msg__VelodyneState__Sequence__are_equal(const velodyne_control_msgs__msg__VelodyneState__Sequence * lhs, const velodyne_control_msgs__msg__VelodyneState__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!velodyne_control_msgs__msg__VelodyneState__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
velodyne_control_msgs__msg__VelodyneState__Sequence__copy(
  const velodyne_control_msgs__msg__VelodyneState__Sequence * input,
  velodyne_control_msgs__msg__VelodyneState__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(velodyne_control_msgs__msg__VelodyneState);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    velodyne_control_msgs__msg__VelodyneState * data =
      (velodyne_control_msgs__msg__VelodyneState *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!velodyne_control_msgs__msg__VelodyneState__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          velodyne_control_msgs__msg__VelodyneState__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!velodyne_control_msgs__msg__VelodyneState__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
