// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from my_joystick_msgs:msg/Joystick.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "my_joystick_msgs/msg/joystick.hpp"


#ifndef MY_JOYSTICK_MSGS__MSG__DETAIL__JOYSTICK__STRUCT_HPP_
#define MY_JOYSTICK_MSGS__MSG__DETAIL__JOYSTICK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__my_joystick_msgs__msg__Joystick __attribute__((deprecated))
#else
# define DEPRECATED__my_joystick_msgs__msg__Joystick __declspec(deprecated)
#endif

namespace my_joystick_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Joystick_
{
  using Type = Joystick_<ContainerAllocator>;

  explicit Joystick_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lx = 0l;
      this->ly = 0l;
      this->rx = 0l;
      this->ry = 0l;
      this->dx = 0l;
      this->dy = 0l;
      this->l2 = 0l;
      this->r2 = 0l;
      this->a = false;
      this->b = false;
      this->x = false;
      this->y = false;
      this->l1 = false;
      this->r1 = false;
      this->l3 = false;
      this->r3 = false;
      this->select = false;
      this->start = false;
    }
  }

  explicit Joystick_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lx = 0l;
      this->ly = 0l;
      this->rx = 0l;
      this->ry = 0l;
      this->dx = 0l;
      this->dy = 0l;
      this->l2 = 0l;
      this->r2 = 0l;
      this->a = false;
      this->b = false;
      this->x = false;
      this->y = false;
      this->l1 = false;
      this->r1 = false;
      this->l3 = false;
      this->r3 = false;
      this->select = false;
      this->start = false;
    }
  }

  // field types and members
  using _lx_type =
    int32_t;
  _lx_type lx;
  using _ly_type =
    int32_t;
  _ly_type ly;
  using _rx_type =
    int32_t;
  _rx_type rx;
  using _ry_type =
    int32_t;
  _ry_type ry;
  using _dx_type =
    int32_t;
  _dx_type dx;
  using _dy_type =
    int32_t;
  _dy_type dy;
  using _l2_type =
    int32_t;
  _l2_type l2;
  using _r2_type =
    int32_t;
  _r2_type r2;
  using _a_type =
    bool;
  _a_type a;
  using _b_type =
    bool;
  _b_type b;
  using _x_type =
    bool;
  _x_type x;
  using _y_type =
    bool;
  _y_type y;
  using _l1_type =
    bool;
  _l1_type l1;
  using _r1_type =
    bool;
  _r1_type r1;
  using _l3_type =
    bool;
  _l3_type l3;
  using _r3_type =
    bool;
  _r3_type r3;
  using _select_type =
    bool;
  _select_type select;
  using _start_type =
    bool;
  _start_type start;

  // setters for named parameter idiom
  Type & set__lx(
    const int32_t & _arg)
  {
    this->lx = _arg;
    return *this;
  }
  Type & set__ly(
    const int32_t & _arg)
  {
    this->ly = _arg;
    return *this;
  }
  Type & set__rx(
    const int32_t & _arg)
  {
    this->rx = _arg;
    return *this;
  }
  Type & set__ry(
    const int32_t & _arg)
  {
    this->ry = _arg;
    return *this;
  }
  Type & set__dx(
    const int32_t & _arg)
  {
    this->dx = _arg;
    return *this;
  }
  Type & set__dy(
    const int32_t & _arg)
  {
    this->dy = _arg;
    return *this;
  }
  Type & set__l2(
    const int32_t & _arg)
  {
    this->l2 = _arg;
    return *this;
  }
  Type & set__r2(
    const int32_t & _arg)
  {
    this->r2 = _arg;
    return *this;
  }
  Type & set__a(
    const bool & _arg)
  {
    this->a = _arg;
    return *this;
  }
  Type & set__b(
    const bool & _arg)
  {
    this->b = _arg;
    return *this;
  }
  Type & set__x(
    const bool & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const bool & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__l1(
    const bool & _arg)
  {
    this->l1 = _arg;
    return *this;
  }
  Type & set__r1(
    const bool & _arg)
  {
    this->r1 = _arg;
    return *this;
  }
  Type & set__l3(
    const bool & _arg)
  {
    this->l3 = _arg;
    return *this;
  }
  Type & set__r3(
    const bool & _arg)
  {
    this->r3 = _arg;
    return *this;
  }
  Type & set__select(
    const bool & _arg)
  {
    this->select = _arg;
    return *this;
  }
  Type & set__start(
    const bool & _arg)
  {
    this->start = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    my_joystick_msgs::msg::Joystick_<ContainerAllocator> *;
  using ConstRawPtr =
    const my_joystick_msgs::msg::Joystick_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<my_joystick_msgs::msg::Joystick_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<my_joystick_msgs::msg::Joystick_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      my_joystick_msgs::msg::Joystick_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<my_joystick_msgs::msg::Joystick_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      my_joystick_msgs::msg::Joystick_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<my_joystick_msgs::msg::Joystick_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<my_joystick_msgs::msg::Joystick_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<my_joystick_msgs::msg::Joystick_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__my_joystick_msgs__msg__Joystick
    std::shared_ptr<my_joystick_msgs::msg::Joystick_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__my_joystick_msgs__msg__Joystick
    std::shared_ptr<my_joystick_msgs::msg::Joystick_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Joystick_ & other) const
  {
    if (this->lx != other.lx) {
      return false;
    }
    if (this->ly != other.ly) {
      return false;
    }
    if (this->rx != other.rx) {
      return false;
    }
    if (this->ry != other.ry) {
      return false;
    }
    if (this->dx != other.dx) {
      return false;
    }
    if (this->dy != other.dy) {
      return false;
    }
    if (this->l2 != other.l2) {
      return false;
    }
    if (this->r2 != other.r2) {
      return false;
    }
    if (this->a != other.a) {
      return false;
    }
    if (this->b != other.b) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->l1 != other.l1) {
      return false;
    }
    if (this->r1 != other.r1) {
      return false;
    }
    if (this->l3 != other.l3) {
      return false;
    }
    if (this->r3 != other.r3) {
      return false;
    }
    if (this->select != other.select) {
      return false;
    }
    if (this->start != other.start) {
      return false;
    }
    return true;
  }
  bool operator!=(const Joystick_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Joystick_

// alias to use template instance with default allocator
using Joystick =
  my_joystick_msgs::msg::Joystick_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace my_joystick_msgs

#endif  // MY_JOYSTICK_MSGS__MSG__DETAIL__JOYSTICK__STRUCT_HPP_
