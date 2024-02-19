// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from velodyne_control_msgs:srv/VelodyneControl.idl
// generated code does not contain a copyright notice
#include "velodyne_control_msgs/srv/detail/velodyne_control__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
velodyne_control_msgs__srv__VelodyneControl_Request__init(velodyne_control_msgs__srv__VelodyneControl_Request * msg)
{
  if (!msg) {
    return false;
  }
  // velocity
  return true;
}

void
velodyne_control_msgs__srv__VelodyneControl_Request__fini(velodyne_control_msgs__srv__VelodyneControl_Request * msg)
{
  if (!msg) {
    return;
  }
  // velocity
}

bool
velodyne_control_msgs__srv__VelodyneControl_Request__are_equal(const velodyne_control_msgs__srv__VelodyneControl_Request * lhs, const velodyne_control_msgs__srv__VelodyneControl_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // velocity
  if (lhs->velocity != rhs->velocity) {
    return false;
  }
  return true;
}

bool
velodyne_control_msgs__srv__VelodyneControl_Request__copy(
  const velodyne_control_msgs__srv__VelodyneControl_Request * input,
  velodyne_control_msgs__srv__VelodyneControl_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // velocity
  output->velocity = input->velocity;
  return true;
}

velodyne_control_msgs__srv__VelodyneControl_Request *
velodyne_control_msgs__srv__VelodyneControl_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  velodyne_control_msgs__srv__VelodyneControl_Request * msg = (velodyne_control_msgs__srv__VelodyneControl_Request *)allocator.allocate(sizeof(velodyne_control_msgs__srv__VelodyneControl_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(velodyne_control_msgs__srv__VelodyneControl_Request));
  bool success = velodyne_control_msgs__srv__VelodyneControl_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
velodyne_control_msgs__srv__VelodyneControl_Request__destroy(velodyne_control_msgs__srv__VelodyneControl_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    velodyne_control_msgs__srv__VelodyneControl_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
velodyne_control_msgs__srv__VelodyneControl_Request__Sequence__init(velodyne_control_msgs__srv__VelodyneControl_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  velodyne_control_msgs__srv__VelodyneControl_Request * data = NULL;

  if (size) {
    data = (velodyne_control_msgs__srv__VelodyneControl_Request *)allocator.zero_allocate(size, sizeof(velodyne_control_msgs__srv__VelodyneControl_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = velodyne_control_msgs__srv__VelodyneControl_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        velodyne_control_msgs__srv__VelodyneControl_Request__fini(&data[i - 1]);
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
velodyne_control_msgs__srv__VelodyneControl_Request__Sequence__fini(velodyne_control_msgs__srv__VelodyneControl_Request__Sequence * array)
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
      velodyne_control_msgs__srv__VelodyneControl_Request__fini(&array->data[i]);
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

velodyne_control_msgs__srv__VelodyneControl_Request__Sequence *
velodyne_control_msgs__srv__VelodyneControl_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  velodyne_control_msgs__srv__VelodyneControl_Request__Sequence * array = (velodyne_control_msgs__srv__VelodyneControl_Request__Sequence *)allocator.allocate(sizeof(velodyne_control_msgs__srv__VelodyneControl_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = velodyne_control_msgs__srv__VelodyneControl_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
velodyne_control_msgs__srv__VelodyneControl_Request__Sequence__destroy(velodyne_control_msgs__srv__VelodyneControl_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    velodyne_control_msgs__srv__VelodyneControl_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
velodyne_control_msgs__srv__VelodyneControl_Request__Sequence__are_equal(const velodyne_control_msgs__srv__VelodyneControl_Request__Sequence * lhs, const velodyne_control_msgs__srv__VelodyneControl_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!velodyne_control_msgs__srv__VelodyneControl_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
velodyne_control_msgs__srv__VelodyneControl_Request__Sequence__copy(
  const velodyne_control_msgs__srv__VelodyneControl_Request__Sequence * input,
  velodyne_control_msgs__srv__VelodyneControl_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(velodyne_control_msgs__srv__VelodyneControl_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    velodyne_control_msgs__srv__VelodyneControl_Request * data =
      (velodyne_control_msgs__srv__VelodyneControl_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!velodyne_control_msgs__srv__VelodyneControl_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          velodyne_control_msgs__srv__VelodyneControl_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!velodyne_control_msgs__srv__VelodyneControl_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
velodyne_control_msgs__srv__VelodyneControl_Response__init(velodyne_control_msgs__srv__VelodyneControl_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  return true;
}

void
velodyne_control_msgs__srv__VelodyneControl_Response__fini(velodyne_control_msgs__srv__VelodyneControl_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
}

bool
velodyne_control_msgs__srv__VelodyneControl_Response__are_equal(const velodyne_control_msgs__srv__VelodyneControl_Response * lhs, const velodyne_control_msgs__srv__VelodyneControl_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  return true;
}

bool
velodyne_control_msgs__srv__VelodyneControl_Response__copy(
  const velodyne_control_msgs__srv__VelodyneControl_Response * input,
  velodyne_control_msgs__srv__VelodyneControl_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  return true;
}

velodyne_control_msgs__srv__VelodyneControl_Response *
velodyne_control_msgs__srv__VelodyneControl_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  velodyne_control_msgs__srv__VelodyneControl_Response * msg = (velodyne_control_msgs__srv__VelodyneControl_Response *)allocator.allocate(sizeof(velodyne_control_msgs__srv__VelodyneControl_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(velodyne_control_msgs__srv__VelodyneControl_Response));
  bool success = velodyne_control_msgs__srv__VelodyneControl_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
velodyne_control_msgs__srv__VelodyneControl_Response__destroy(velodyne_control_msgs__srv__VelodyneControl_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    velodyne_control_msgs__srv__VelodyneControl_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
velodyne_control_msgs__srv__VelodyneControl_Response__Sequence__init(velodyne_control_msgs__srv__VelodyneControl_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  velodyne_control_msgs__srv__VelodyneControl_Response * data = NULL;

  if (size) {
    data = (velodyne_control_msgs__srv__VelodyneControl_Response *)allocator.zero_allocate(size, sizeof(velodyne_control_msgs__srv__VelodyneControl_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = velodyne_control_msgs__srv__VelodyneControl_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        velodyne_control_msgs__srv__VelodyneControl_Response__fini(&data[i - 1]);
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
velodyne_control_msgs__srv__VelodyneControl_Response__Sequence__fini(velodyne_control_msgs__srv__VelodyneControl_Response__Sequence * array)
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
      velodyne_control_msgs__srv__VelodyneControl_Response__fini(&array->data[i]);
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

velodyne_control_msgs__srv__VelodyneControl_Response__Sequence *
velodyne_control_msgs__srv__VelodyneControl_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  velodyne_control_msgs__srv__VelodyneControl_Response__Sequence * array = (velodyne_control_msgs__srv__VelodyneControl_Response__Sequence *)allocator.allocate(sizeof(velodyne_control_msgs__srv__VelodyneControl_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = velodyne_control_msgs__srv__VelodyneControl_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
velodyne_control_msgs__srv__VelodyneControl_Response__Sequence__destroy(velodyne_control_msgs__srv__VelodyneControl_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    velodyne_control_msgs__srv__VelodyneControl_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
velodyne_control_msgs__srv__VelodyneControl_Response__Sequence__are_equal(const velodyne_control_msgs__srv__VelodyneControl_Response__Sequence * lhs, const velodyne_control_msgs__srv__VelodyneControl_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!velodyne_control_msgs__srv__VelodyneControl_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
velodyne_control_msgs__srv__VelodyneControl_Response__Sequence__copy(
  const velodyne_control_msgs__srv__VelodyneControl_Response__Sequence * input,
  velodyne_control_msgs__srv__VelodyneControl_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(velodyne_control_msgs__srv__VelodyneControl_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    velodyne_control_msgs__srv__VelodyneControl_Response * data =
      (velodyne_control_msgs__srv__VelodyneControl_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!velodyne_control_msgs__srv__VelodyneControl_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          velodyne_control_msgs__srv__VelodyneControl_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!velodyne_control_msgs__srv__VelodyneControl_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
