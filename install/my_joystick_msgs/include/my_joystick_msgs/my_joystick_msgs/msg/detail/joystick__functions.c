// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from my_joystick_msgs:msg/Joystick.idl
// generated code does not contain a copyright notice
#include "my_joystick_msgs/msg/detail/joystick__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
my_joystick_msgs__msg__Joystick__init(my_joystick_msgs__msg__Joystick * msg)
{
  if (!msg) {
    return false;
  }
  // lx
  // ly
  // rx
  // ry
  // dx
  // dy
  // l2
  // r2
  // a
  // b
  // x
  // y
  // l1
  // r1
  // l3
  // r3
  // select
  // start
  return true;
}

void
my_joystick_msgs__msg__Joystick__fini(my_joystick_msgs__msg__Joystick * msg)
{
  if (!msg) {
    return;
  }
  // lx
  // ly
  // rx
  // ry
  // dx
  // dy
  // l2
  // r2
  // a
  // b
  // x
  // y
  // l1
  // r1
  // l3
  // r3
  // select
  // start
}

bool
my_joystick_msgs__msg__Joystick__are_equal(const my_joystick_msgs__msg__Joystick * lhs, const my_joystick_msgs__msg__Joystick * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // lx
  if (lhs->lx != rhs->lx) {
    return false;
  }
  // ly
  if (lhs->ly != rhs->ly) {
    return false;
  }
  // rx
  if (lhs->rx != rhs->rx) {
    return false;
  }
  // ry
  if (lhs->ry != rhs->ry) {
    return false;
  }
  // dx
  if (lhs->dx != rhs->dx) {
    return false;
  }
  // dy
  if (lhs->dy != rhs->dy) {
    return false;
  }
  // l2
  if (lhs->l2 != rhs->l2) {
    return false;
  }
  // r2
  if (lhs->r2 != rhs->r2) {
    return false;
  }
  // a
  if (lhs->a != rhs->a) {
    return false;
  }
  // b
  if (lhs->b != rhs->b) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // l1
  if (lhs->l1 != rhs->l1) {
    return false;
  }
  // r1
  if (lhs->r1 != rhs->r1) {
    return false;
  }
  // l3
  if (lhs->l3 != rhs->l3) {
    return false;
  }
  // r3
  if (lhs->r3 != rhs->r3) {
    return false;
  }
  // select
  if (lhs->select != rhs->select) {
    return false;
  }
  // start
  if (lhs->start != rhs->start) {
    return false;
  }
  return true;
}

bool
my_joystick_msgs__msg__Joystick__copy(
  const my_joystick_msgs__msg__Joystick * input,
  my_joystick_msgs__msg__Joystick * output)
{
  if (!input || !output) {
    return false;
  }
  // lx
  output->lx = input->lx;
  // ly
  output->ly = input->ly;
  // rx
  output->rx = input->rx;
  // ry
  output->ry = input->ry;
  // dx
  output->dx = input->dx;
  // dy
  output->dy = input->dy;
  // l2
  output->l2 = input->l2;
  // r2
  output->r2 = input->r2;
  // a
  output->a = input->a;
  // b
  output->b = input->b;
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // l1
  output->l1 = input->l1;
  // r1
  output->r1 = input->r1;
  // l3
  output->l3 = input->l3;
  // r3
  output->r3 = input->r3;
  // select
  output->select = input->select;
  // start
  output->start = input->start;
  return true;
}

my_joystick_msgs__msg__Joystick *
my_joystick_msgs__msg__Joystick__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_joystick_msgs__msg__Joystick * msg = (my_joystick_msgs__msg__Joystick *)allocator.allocate(sizeof(my_joystick_msgs__msg__Joystick), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(my_joystick_msgs__msg__Joystick));
  bool success = my_joystick_msgs__msg__Joystick__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
my_joystick_msgs__msg__Joystick__destroy(my_joystick_msgs__msg__Joystick * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    my_joystick_msgs__msg__Joystick__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
my_joystick_msgs__msg__Joystick__Sequence__init(my_joystick_msgs__msg__Joystick__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_joystick_msgs__msg__Joystick * data = NULL;

  if (size) {
    data = (my_joystick_msgs__msg__Joystick *)allocator.zero_allocate(size, sizeof(my_joystick_msgs__msg__Joystick), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = my_joystick_msgs__msg__Joystick__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        my_joystick_msgs__msg__Joystick__fini(&data[i - 1]);
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
my_joystick_msgs__msg__Joystick__Sequence__fini(my_joystick_msgs__msg__Joystick__Sequence * array)
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
      my_joystick_msgs__msg__Joystick__fini(&array->data[i]);
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

my_joystick_msgs__msg__Joystick__Sequence *
my_joystick_msgs__msg__Joystick__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  my_joystick_msgs__msg__Joystick__Sequence * array = (my_joystick_msgs__msg__Joystick__Sequence *)allocator.allocate(sizeof(my_joystick_msgs__msg__Joystick__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = my_joystick_msgs__msg__Joystick__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
my_joystick_msgs__msg__Joystick__Sequence__destroy(my_joystick_msgs__msg__Joystick__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    my_joystick_msgs__msg__Joystick__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
my_joystick_msgs__msg__Joystick__Sequence__are_equal(const my_joystick_msgs__msg__Joystick__Sequence * lhs, const my_joystick_msgs__msg__Joystick__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!my_joystick_msgs__msg__Joystick__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
my_joystick_msgs__msg__Joystick__Sequence__copy(
  const my_joystick_msgs__msg__Joystick__Sequence * input,
  my_joystick_msgs__msg__Joystick__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(my_joystick_msgs__msg__Joystick);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    my_joystick_msgs__msg__Joystick * data =
      (my_joystick_msgs__msg__Joystick *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!my_joystick_msgs__msg__Joystick__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          my_joystick_msgs__msg__Joystick__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!my_joystick_msgs__msg__Joystick__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
