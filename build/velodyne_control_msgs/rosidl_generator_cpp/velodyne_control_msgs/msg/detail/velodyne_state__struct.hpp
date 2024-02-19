// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from velodyne_control_msgs:msg/VelodyneState.idl
// generated code does not contain a copyright notice

#ifndef VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__STRUCT_HPP_
#define VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__velodyne_control_msgs__msg__VelodyneState __attribute__((deprecated))
#else
# define DEPRECATED__velodyne_control_msgs__msg__VelodyneState __declspec(deprecated)
#endif

namespace velodyne_control_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VelodyneState_
{
  using Type = VelodyneState_<ContainerAllocator>;

  explicit VelodyneState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velocity = 0.0;
      this->enabled = false;
    }
  }

  explicit VelodyneState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velocity = 0.0;
      this->enabled = false;
    }
  }

  // field types and members
  using _velocity_type =
    double;
  _velocity_type velocity;
  using _enabled_type =
    bool;
  _enabled_type enabled;

  // setters for named parameter idiom
  Type & set__velocity(
    const double & _arg)
  {
    this->velocity = _arg;
    return *this;
  }
  Type & set__enabled(
    const bool & _arg)
  {
    this->enabled = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    velodyne_control_msgs::msg::VelodyneState_<ContainerAllocator> *;
  using ConstRawPtr =
    const velodyne_control_msgs::msg::VelodyneState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<velodyne_control_msgs::msg::VelodyneState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<velodyne_control_msgs::msg::VelodyneState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      velodyne_control_msgs::msg::VelodyneState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<velodyne_control_msgs::msg::VelodyneState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      velodyne_control_msgs::msg::VelodyneState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<velodyne_control_msgs::msg::VelodyneState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<velodyne_control_msgs::msg::VelodyneState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<velodyne_control_msgs::msg::VelodyneState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__velodyne_control_msgs__msg__VelodyneState
    std::shared_ptr<velodyne_control_msgs::msg::VelodyneState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__velodyne_control_msgs__msg__VelodyneState
    std::shared_ptr<velodyne_control_msgs::msg::VelodyneState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VelodyneState_ & other) const
  {
    if (this->velocity != other.velocity) {
      return false;
    }
    if (this->enabled != other.enabled) {
      return false;
    }
    return true;
  }
  bool operator!=(const VelodyneState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VelodyneState_

// alias to use template instance with default allocator
using VelodyneState =
  velodyne_control_msgs::msg::VelodyneState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace velodyne_control_msgs

#endif  // VELODYNE_CONTROL_MSGS__MSG__DETAIL__VELODYNE_STATE__STRUCT_HPP_
