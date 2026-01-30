// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_joystick_msgs:msg/Joystick.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "my_joystick_msgs/msg/joystick.hpp"


#ifndef MY_JOYSTICK_MSGS__MSG__DETAIL__JOYSTICK__BUILDER_HPP_
#define MY_JOYSTICK_MSGS__MSG__DETAIL__JOYSTICK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_joystick_msgs/msg/detail/joystick__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_joystick_msgs
{

namespace msg
{

namespace builder
{

class Init_Joystick_start
{
public:
  explicit Init_Joystick_start(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  ::my_joystick_msgs::msg::Joystick start(::my_joystick_msgs::msg::Joystick::_start_type arg)
  {
    msg_.start = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_select
{
public:
  explicit Init_Joystick_select(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_start select(::my_joystick_msgs::msg::Joystick::_select_type arg)
  {
    msg_.select = std::move(arg);
    return Init_Joystick_start(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_r3
{
public:
  explicit Init_Joystick_r3(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_select r3(::my_joystick_msgs::msg::Joystick::_r3_type arg)
  {
    msg_.r3 = std::move(arg);
    return Init_Joystick_select(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_l3
{
public:
  explicit Init_Joystick_l3(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_r3 l3(::my_joystick_msgs::msg::Joystick::_l3_type arg)
  {
    msg_.l3 = std::move(arg);
    return Init_Joystick_r3(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_r1
{
public:
  explicit Init_Joystick_r1(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_l3 r1(::my_joystick_msgs::msg::Joystick::_r1_type arg)
  {
    msg_.r1 = std::move(arg);
    return Init_Joystick_l3(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_l1
{
public:
  explicit Init_Joystick_l1(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_r1 l1(::my_joystick_msgs::msg::Joystick::_l1_type arg)
  {
    msg_.l1 = std::move(arg);
    return Init_Joystick_r1(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_y
{
public:
  explicit Init_Joystick_y(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_l1 y(::my_joystick_msgs::msg::Joystick::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Joystick_l1(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_x
{
public:
  explicit Init_Joystick_x(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_y x(::my_joystick_msgs::msg::Joystick::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Joystick_y(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_b
{
public:
  explicit Init_Joystick_b(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_x b(::my_joystick_msgs::msg::Joystick::_b_type arg)
  {
    msg_.b = std::move(arg);
    return Init_Joystick_x(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_a
{
public:
  explicit Init_Joystick_a(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_b a(::my_joystick_msgs::msg::Joystick::_a_type arg)
  {
    msg_.a = std::move(arg);
    return Init_Joystick_b(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_r2
{
public:
  explicit Init_Joystick_r2(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_a r2(::my_joystick_msgs::msg::Joystick::_r2_type arg)
  {
    msg_.r2 = std::move(arg);
    return Init_Joystick_a(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_l2
{
public:
  explicit Init_Joystick_l2(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_r2 l2(::my_joystick_msgs::msg::Joystick::_l2_type arg)
  {
    msg_.l2 = std::move(arg);
    return Init_Joystick_r2(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_dy
{
public:
  explicit Init_Joystick_dy(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_l2 dy(::my_joystick_msgs::msg::Joystick::_dy_type arg)
  {
    msg_.dy = std::move(arg);
    return Init_Joystick_l2(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_dx
{
public:
  explicit Init_Joystick_dx(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_dy dx(::my_joystick_msgs::msg::Joystick::_dx_type arg)
  {
    msg_.dx = std::move(arg);
    return Init_Joystick_dy(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_ry
{
public:
  explicit Init_Joystick_ry(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_dx ry(::my_joystick_msgs::msg::Joystick::_ry_type arg)
  {
    msg_.ry = std::move(arg);
    return Init_Joystick_dx(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_rx
{
public:
  explicit Init_Joystick_rx(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_ry rx(::my_joystick_msgs::msg::Joystick::_rx_type arg)
  {
    msg_.rx = std::move(arg);
    return Init_Joystick_ry(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_ly
{
public:
  explicit Init_Joystick_ly(::my_joystick_msgs::msg::Joystick & msg)
  : msg_(msg)
  {}
  Init_Joystick_rx ly(::my_joystick_msgs::msg::Joystick::_ly_type arg)
  {
    msg_.ly = std::move(arg);
    return Init_Joystick_rx(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

class Init_Joystick_lx
{
public:
  Init_Joystick_lx()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Joystick_ly lx(::my_joystick_msgs::msg::Joystick::_lx_type arg)
  {
    msg_.lx = std::move(arg);
    return Init_Joystick_ly(msg_);
  }

private:
  ::my_joystick_msgs::msg::Joystick msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_joystick_msgs::msg::Joystick>()
{
  return my_joystick_msgs::msg::builder::Init_Joystick_lx();
}

}  // namespace my_joystick_msgs

#endif  // MY_JOYSTICK_MSGS__MSG__DETAIL__JOYSTICK__BUILDER_HPP_
