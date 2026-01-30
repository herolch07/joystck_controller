// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from my_joystick_msgs:msg/Joystick.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "my_joystick_msgs/msg/joystick.h"


#ifndef MY_JOYSTICK_MSGS__MSG__DETAIL__JOYSTICK__STRUCT_H_
#define MY_JOYSTICK_MSGS__MSG__DETAIL__JOYSTICK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Joystick in the package my_joystick_msgs.
/**
  * Joystick.msg
 */
typedef struct my_joystick_msgs__msg__Joystick
{
  /// Axes (analog inputs) - Normalized to -8192 ~ 8192 range for better precision
  int32_t lx;
  int32_t ly;
  int32_t rx;
  int32_t ry;
  int32_t dx;
  int32_t dy;
  int32_t l2;
  int32_t r2;
  /// Buttons (digital inputs)
  bool a;
  bool b;
  bool x;
  bool y;
  bool l1;
  bool r1;
  bool l3;
  bool r3;
  bool select;
  bool start;
} my_joystick_msgs__msg__Joystick;

// Struct for a sequence of my_joystick_msgs__msg__Joystick.
typedef struct my_joystick_msgs__msg__Joystick__Sequence
{
  my_joystick_msgs__msg__Joystick * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} my_joystick_msgs__msg__Joystick__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MY_JOYSTICK_MSGS__MSG__DETAIL__JOYSTICK__STRUCT_H_
