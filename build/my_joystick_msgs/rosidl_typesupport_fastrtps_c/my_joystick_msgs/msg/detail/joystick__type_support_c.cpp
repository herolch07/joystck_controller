// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from my_joystick_msgs:msg/Joystick.idl
// generated code does not contain a copyright notice
#include "my_joystick_msgs/msg/detail/joystick__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "my_joystick_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "my_joystick_msgs/msg/detail/joystick__struct.h"
#include "my_joystick_msgs/msg/detail/joystick__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _Joystick__ros_msg_type = my_joystick_msgs__msg__Joystick;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_joystick_msgs
bool cdr_serialize_my_joystick_msgs__msg__Joystick(
  const my_joystick_msgs__msg__Joystick * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: lx
  {
    cdr << ros_message->lx;
  }

  // Field name: ly
  {
    cdr << ros_message->ly;
  }

  // Field name: rx
  {
    cdr << ros_message->rx;
  }

  // Field name: ry
  {
    cdr << ros_message->ry;
  }

  // Field name: dx
  {
    cdr << ros_message->dx;
  }

  // Field name: dy
  {
    cdr << ros_message->dy;
  }

  // Field name: l2
  {
    cdr << ros_message->l2;
  }

  // Field name: r2
  {
    cdr << ros_message->r2;
  }

  // Field name: a
  {
    cdr << (ros_message->a ? true : false);
  }

  // Field name: b
  {
    cdr << (ros_message->b ? true : false);
  }

  // Field name: x
  {
    cdr << (ros_message->x ? true : false);
  }

  // Field name: y
  {
    cdr << (ros_message->y ? true : false);
  }

  // Field name: l1
  {
    cdr << (ros_message->l1 ? true : false);
  }

  // Field name: r1
  {
    cdr << (ros_message->r1 ? true : false);
  }

  // Field name: l3
  {
    cdr << (ros_message->l3 ? true : false);
  }

  // Field name: r3
  {
    cdr << (ros_message->r3 ? true : false);
  }

  // Field name: select
  {
    cdr << (ros_message->select ? true : false);
  }

  // Field name: start
  {
    cdr << (ros_message->start ? true : false);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_joystick_msgs
bool cdr_deserialize_my_joystick_msgs__msg__Joystick(
  eprosima::fastcdr::Cdr & cdr,
  my_joystick_msgs__msg__Joystick * ros_message)
{
  // Field name: lx
  {
    cdr >> ros_message->lx;
  }

  // Field name: ly
  {
    cdr >> ros_message->ly;
  }

  // Field name: rx
  {
    cdr >> ros_message->rx;
  }

  // Field name: ry
  {
    cdr >> ros_message->ry;
  }

  // Field name: dx
  {
    cdr >> ros_message->dx;
  }

  // Field name: dy
  {
    cdr >> ros_message->dy;
  }

  // Field name: l2
  {
    cdr >> ros_message->l2;
  }

  // Field name: r2
  {
    cdr >> ros_message->r2;
  }

  // Field name: a
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->a = tmp ? true : false;
  }

  // Field name: b
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->b = tmp ? true : false;
  }

  // Field name: x
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->x = tmp ? true : false;
  }

  // Field name: y
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->y = tmp ? true : false;
  }

  // Field name: l1
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->l1 = tmp ? true : false;
  }

  // Field name: r1
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->r1 = tmp ? true : false;
  }

  // Field name: l3
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->l3 = tmp ? true : false;
  }

  // Field name: r3
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->r3 = tmp ? true : false;
  }

  // Field name: select
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->select = tmp ? true : false;
  }

  // Field name: start
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->start = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_joystick_msgs
size_t get_serialized_size_my_joystick_msgs__msg__Joystick(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Joystick__ros_msg_type * ros_message = static_cast<const _Joystick__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: lx
  {
    size_t item_size = sizeof(ros_message->lx);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: ly
  {
    size_t item_size = sizeof(ros_message->ly);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: rx
  {
    size_t item_size = sizeof(ros_message->rx);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: ry
  {
    size_t item_size = sizeof(ros_message->ry);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: dx
  {
    size_t item_size = sizeof(ros_message->dx);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: dy
  {
    size_t item_size = sizeof(ros_message->dy);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: l2
  {
    size_t item_size = sizeof(ros_message->l2);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: r2
  {
    size_t item_size = sizeof(ros_message->r2);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: a
  {
    size_t item_size = sizeof(ros_message->a);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: b
  {
    size_t item_size = sizeof(ros_message->b);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: x
  {
    size_t item_size = sizeof(ros_message->x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: y
  {
    size_t item_size = sizeof(ros_message->y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: l1
  {
    size_t item_size = sizeof(ros_message->l1);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: r1
  {
    size_t item_size = sizeof(ros_message->r1);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: l3
  {
    size_t item_size = sizeof(ros_message->l3);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: r3
  {
    size_t item_size = sizeof(ros_message->r3);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: select
  {
    size_t item_size = sizeof(ros_message->select);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: start
  {
    size_t item_size = sizeof(ros_message->start);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_joystick_msgs
size_t max_serialized_size_my_joystick_msgs__msg__Joystick(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: lx
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: ly
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: rx
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: ry
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: dx
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: dy
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: l2
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: r2
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: a
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: b
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: x
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: y
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: l1
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: r1
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: l3
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: r3
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: select
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: start
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = my_joystick_msgs__msg__Joystick;
    is_plain =
      (
      offsetof(DataType, start) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_joystick_msgs
bool cdr_serialize_key_my_joystick_msgs__msg__Joystick(
  const my_joystick_msgs__msg__Joystick * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: lx
  {
    cdr << ros_message->lx;
  }

  // Field name: ly
  {
    cdr << ros_message->ly;
  }

  // Field name: rx
  {
    cdr << ros_message->rx;
  }

  // Field name: ry
  {
    cdr << ros_message->ry;
  }

  // Field name: dx
  {
    cdr << ros_message->dx;
  }

  // Field name: dy
  {
    cdr << ros_message->dy;
  }

  // Field name: l2
  {
    cdr << ros_message->l2;
  }

  // Field name: r2
  {
    cdr << ros_message->r2;
  }

  // Field name: a
  {
    cdr << (ros_message->a ? true : false);
  }

  // Field name: b
  {
    cdr << (ros_message->b ? true : false);
  }

  // Field name: x
  {
    cdr << (ros_message->x ? true : false);
  }

  // Field name: y
  {
    cdr << (ros_message->y ? true : false);
  }

  // Field name: l1
  {
    cdr << (ros_message->l1 ? true : false);
  }

  // Field name: r1
  {
    cdr << (ros_message->r1 ? true : false);
  }

  // Field name: l3
  {
    cdr << (ros_message->l3 ? true : false);
  }

  // Field name: r3
  {
    cdr << (ros_message->r3 ? true : false);
  }

  // Field name: select
  {
    cdr << (ros_message->select ? true : false);
  }

  // Field name: start
  {
    cdr << (ros_message->start ? true : false);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_joystick_msgs
size_t get_serialized_size_key_my_joystick_msgs__msg__Joystick(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Joystick__ros_msg_type * ros_message = static_cast<const _Joystick__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: lx
  {
    size_t item_size = sizeof(ros_message->lx);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: ly
  {
    size_t item_size = sizeof(ros_message->ly);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: rx
  {
    size_t item_size = sizeof(ros_message->rx);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: ry
  {
    size_t item_size = sizeof(ros_message->ry);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: dx
  {
    size_t item_size = sizeof(ros_message->dx);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: dy
  {
    size_t item_size = sizeof(ros_message->dy);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: l2
  {
    size_t item_size = sizeof(ros_message->l2);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: r2
  {
    size_t item_size = sizeof(ros_message->r2);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: a
  {
    size_t item_size = sizeof(ros_message->a);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: b
  {
    size_t item_size = sizeof(ros_message->b);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: x
  {
    size_t item_size = sizeof(ros_message->x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: y
  {
    size_t item_size = sizeof(ros_message->y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: l1
  {
    size_t item_size = sizeof(ros_message->l1);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: r1
  {
    size_t item_size = sizeof(ros_message->r1);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: l3
  {
    size_t item_size = sizeof(ros_message->l3);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: r3
  {
    size_t item_size = sizeof(ros_message->r3);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: select
  {
    size_t item_size = sizeof(ros_message->select);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: start
  {
    size_t item_size = sizeof(ros_message->start);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_my_joystick_msgs
size_t max_serialized_size_key_my_joystick_msgs__msg__Joystick(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: lx
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: ly
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: rx
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: ry
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: dx
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: dy
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: l2
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: r2
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: a
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: b
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: x
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: y
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: l1
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: r1
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: l3
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: r3
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: select
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Field name: start
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = my_joystick_msgs__msg__Joystick;
    is_plain =
      (
      offsetof(DataType, start) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _Joystick__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const my_joystick_msgs__msg__Joystick * ros_message = static_cast<const my_joystick_msgs__msg__Joystick *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_my_joystick_msgs__msg__Joystick(ros_message, cdr);
}

static bool _Joystick__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  my_joystick_msgs__msg__Joystick * ros_message = static_cast<my_joystick_msgs__msg__Joystick *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_my_joystick_msgs__msg__Joystick(cdr, ros_message);
}

static uint32_t _Joystick__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_my_joystick_msgs__msg__Joystick(
      untyped_ros_message, 0));
}

static size_t _Joystick__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_my_joystick_msgs__msg__Joystick(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Joystick = {
  "my_joystick_msgs::msg",
  "Joystick",
  _Joystick__cdr_serialize,
  _Joystick__cdr_deserialize,
  _Joystick__get_serialized_size,
  _Joystick__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _Joystick__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Joystick,
  get_message_typesupport_handle_function,
  &my_joystick_msgs__msg__Joystick__get_type_hash,
  &my_joystick_msgs__msg__Joystick__get_type_description,
  &my_joystick_msgs__msg__Joystick__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, my_joystick_msgs, msg, Joystick)() {
  return &_Joystick__type_support;
}

#if defined(__cplusplus)
}
#endif
