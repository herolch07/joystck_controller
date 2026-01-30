// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from my_joystick_msgs:msg/Joystick.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "my_joystick_msgs/msg/joystick.hpp"


#ifndef MY_JOYSTICK_MSGS__MSG__DETAIL__JOYSTICK__TRAITS_HPP_
#define MY_JOYSTICK_MSGS__MSG__DETAIL__JOYSTICK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "my_joystick_msgs/msg/detail/joystick__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace my_joystick_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Joystick & msg,
  std::ostream & out)
{
  out << "{";
  // member: lx
  {
    out << "lx: ";
    rosidl_generator_traits::value_to_yaml(msg.lx, out);
    out << ", ";
  }

  // member: ly
  {
    out << "ly: ";
    rosidl_generator_traits::value_to_yaml(msg.ly, out);
    out << ", ";
  }

  // member: rx
  {
    out << "rx: ";
    rosidl_generator_traits::value_to_yaml(msg.rx, out);
    out << ", ";
  }

  // member: ry
  {
    out << "ry: ";
    rosidl_generator_traits::value_to_yaml(msg.ry, out);
    out << ", ";
  }

  // member: dx
  {
    out << "dx: ";
    rosidl_generator_traits::value_to_yaml(msg.dx, out);
    out << ", ";
  }

  // member: dy
  {
    out << "dy: ";
    rosidl_generator_traits::value_to_yaml(msg.dy, out);
    out << ", ";
  }

  // member: l2
  {
    out << "l2: ";
    rosidl_generator_traits::value_to_yaml(msg.l2, out);
    out << ", ";
  }

  // member: r2
  {
    out << "r2: ";
    rosidl_generator_traits::value_to_yaml(msg.r2, out);
    out << ", ";
  }

  // member: a
  {
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << ", ";
  }

  // member: b
  {
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << ", ";
  }

  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: l1
  {
    out << "l1: ";
    rosidl_generator_traits::value_to_yaml(msg.l1, out);
    out << ", ";
  }

  // member: r1
  {
    out << "r1: ";
    rosidl_generator_traits::value_to_yaml(msg.r1, out);
    out << ", ";
  }

  // member: l3
  {
    out << "l3: ";
    rosidl_generator_traits::value_to_yaml(msg.l3, out);
    out << ", ";
  }

  // member: r3
  {
    out << "r3: ";
    rosidl_generator_traits::value_to_yaml(msg.r3, out);
    out << ", ";
  }

  // member: select
  {
    out << "select: ";
    rosidl_generator_traits::value_to_yaml(msg.select, out);
    out << ", ";
  }

  // member: start
  {
    out << "start: ";
    rosidl_generator_traits::value_to_yaml(msg.start, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Joystick & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: lx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lx: ";
    rosidl_generator_traits::value_to_yaml(msg.lx, out);
    out << "\n";
  }

  // member: ly
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ly: ";
    rosidl_generator_traits::value_to_yaml(msg.ly, out);
    out << "\n";
  }

  // member: rx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "rx: ";
    rosidl_generator_traits::value_to_yaml(msg.rx, out);
    out << "\n";
  }

  // member: ry
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ry: ";
    rosidl_generator_traits::value_to_yaml(msg.ry, out);
    out << "\n";
  }

  // member: dx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dx: ";
    rosidl_generator_traits::value_to_yaml(msg.dx, out);
    out << "\n";
  }

  // member: dy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "dy: ";
    rosidl_generator_traits::value_to_yaml(msg.dy, out);
    out << "\n";
  }

  // member: l2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "l2: ";
    rosidl_generator_traits::value_to_yaml(msg.l2, out);
    out << "\n";
  }

  // member: r2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "r2: ";
    rosidl_generator_traits::value_to_yaml(msg.r2, out);
    out << "\n";
  }

  // member: a
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << "\n";
  }

  // member: b
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: l1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "l1: ";
    rosidl_generator_traits::value_to_yaml(msg.l1, out);
    out << "\n";
  }

  // member: r1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "r1: ";
    rosidl_generator_traits::value_to_yaml(msg.r1, out);
    out << "\n";
  }

  // member: l3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "l3: ";
    rosidl_generator_traits::value_to_yaml(msg.l3, out);
    out << "\n";
  }

  // member: r3
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "r3: ";
    rosidl_generator_traits::value_to_yaml(msg.r3, out);
    out << "\n";
  }

  // member: select
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "select: ";
    rosidl_generator_traits::value_to_yaml(msg.select, out);
    out << "\n";
  }

  // member: start
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "start: ";
    rosidl_generator_traits::value_to_yaml(msg.start, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Joystick & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace my_joystick_msgs

namespace rosidl_generator_traits
{

[[deprecated("use my_joystick_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const my_joystick_msgs::msg::Joystick & msg,
  std::ostream & out, size_t indentation = 0)
{
  my_joystick_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use my_joystick_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const my_joystick_msgs::msg::Joystick & msg)
{
  return my_joystick_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<my_joystick_msgs::msg::Joystick>()
{
  return "my_joystick_msgs::msg::Joystick";
}

template<>
inline const char * name<my_joystick_msgs::msg::Joystick>()
{
  return "my_joystick_msgs/msg/Joystick";
}

template<>
struct has_fixed_size<my_joystick_msgs::msg::Joystick>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<my_joystick_msgs::msg::Joystick>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<my_joystick_msgs::msg::Joystick>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MY_JOYSTICK_MSGS__MSG__DETAIL__JOYSTICK__TRAITS_HPP_
