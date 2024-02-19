// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from velodyne_control_msgs:srv/VelodyneControl.idl
// generated code does not contain a copyright notice

#ifndef VELODYNE_CONTROL_MSGS__SRV__DETAIL__VELODYNE_CONTROL__STRUCT_HPP_
#define VELODYNE_CONTROL_MSGS__SRV__DETAIL__VELODYNE_CONTROL__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__velodyne_control_msgs__srv__VelodyneControl_Request __attribute__((deprecated))
#else
# define DEPRECATED__velodyne_control_msgs__srv__VelodyneControl_Request __declspec(deprecated)
#endif

namespace velodyne_control_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct VelodyneControl_Request_
{
  using Type = VelodyneControl_Request_<ContainerAllocator>;

  explicit VelodyneControl_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velocity = 0.0;
    }
  }

  explicit VelodyneControl_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->velocity = 0.0;
    }
  }

  // field types and members
  using _velocity_type =
    double;
  _velocity_type velocity;

  // setters for named parameter idiom
  Type & set__velocity(
    const double & _arg)
  {
    this->velocity = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    velodyne_control_msgs::srv::VelodyneControl_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const velodyne_control_msgs::srv::VelodyneControl_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<velodyne_control_msgs::srv::VelodyneControl_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<velodyne_control_msgs::srv::VelodyneControl_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      velodyne_control_msgs::srv::VelodyneControl_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<velodyne_control_msgs::srv::VelodyneControl_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      velodyne_control_msgs::srv::VelodyneControl_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<velodyne_control_msgs::srv::VelodyneControl_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<velodyne_control_msgs::srv::VelodyneControl_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<velodyne_control_msgs::srv::VelodyneControl_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__velodyne_control_msgs__srv__VelodyneControl_Request
    std::shared_ptr<velodyne_control_msgs::srv::VelodyneControl_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__velodyne_control_msgs__srv__VelodyneControl_Request
    std::shared_ptr<velodyne_control_msgs::srv::VelodyneControl_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VelodyneControl_Request_ & other) const
  {
    if (this->velocity != other.velocity) {
      return false;
    }
    return true;
  }
  bool operator!=(const VelodyneControl_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VelodyneControl_Request_

// alias to use template instance with default allocator
using VelodyneControl_Request =
  velodyne_control_msgs::srv::VelodyneControl_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace velodyne_control_msgs


#ifndef _WIN32
# define DEPRECATED__velodyne_control_msgs__srv__VelodyneControl_Response __attribute__((deprecated))
#else
# define DEPRECATED__velodyne_control_msgs__srv__VelodyneControl_Response __declspec(deprecated)
#endif

namespace velodyne_control_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct VelodyneControl_Response_
{
  using Type = VelodyneControl_Response_<ContainerAllocator>;

  explicit VelodyneControl_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  explicit VelodyneControl_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    velodyne_control_msgs::srv::VelodyneControl_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const velodyne_control_msgs::srv::VelodyneControl_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<velodyne_control_msgs::srv::VelodyneControl_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<velodyne_control_msgs::srv::VelodyneControl_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      velodyne_control_msgs::srv::VelodyneControl_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<velodyne_control_msgs::srv::VelodyneControl_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      velodyne_control_msgs::srv::VelodyneControl_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<velodyne_control_msgs::srv::VelodyneControl_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<velodyne_control_msgs::srv::VelodyneControl_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<velodyne_control_msgs::srv::VelodyneControl_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__velodyne_control_msgs__srv__VelodyneControl_Response
    std::shared_ptr<velodyne_control_msgs::srv::VelodyneControl_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__velodyne_control_msgs__srv__VelodyneControl_Response
    std::shared_ptr<velodyne_control_msgs::srv::VelodyneControl_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VelodyneControl_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    return true;
  }
  bool operator!=(const VelodyneControl_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VelodyneControl_Response_

// alias to use template instance with default allocator
using VelodyneControl_Response =
  velodyne_control_msgs::srv::VelodyneControl_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace velodyne_control_msgs

namespace velodyne_control_msgs
{

namespace srv
{

struct VelodyneControl
{
  using Request = velodyne_control_msgs::srv::VelodyneControl_Request;
  using Response = velodyne_control_msgs::srv::VelodyneControl_Response;
};

}  // namespace srv

}  // namespace velodyne_control_msgs

#endif  // VELODYNE_CONTROL_MSGS__SRV__DETAIL__VELODYNE_CONTROL__STRUCT_HPP_
