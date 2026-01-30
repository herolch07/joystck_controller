// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from my_joystick_msgs:msg/Joystick.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "my_joystick_msgs/msg/detail/joystick__struct.h"
#include "my_joystick_msgs/msg/detail/joystick__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool my_joystick_msgs__msg__joystick__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[40];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("my_joystick_msgs.msg._joystick.Joystick", full_classname_dest, 39) == 0);
  }
  my_joystick_msgs__msg__Joystick * ros_message = _ros_message;
  {  // lx
    PyObject * field = PyObject_GetAttrString(_pymsg, "lx");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->lx = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // ly
    PyObject * field = PyObject_GetAttrString(_pymsg, "ly");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->ly = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // rx
    PyObject * field = PyObject_GetAttrString(_pymsg, "rx");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->rx = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // ry
    PyObject * field = PyObject_GetAttrString(_pymsg, "ry");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->ry = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // dx
    PyObject * field = PyObject_GetAttrString(_pymsg, "dx");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->dx = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // dy
    PyObject * field = PyObject_GetAttrString(_pymsg, "dy");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->dy = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // l2
    PyObject * field = PyObject_GetAttrString(_pymsg, "l2");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->l2 = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // r2
    PyObject * field = PyObject_GetAttrString(_pymsg, "r2");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->r2 = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // a
    PyObject * field = PyObject_GetAttrString(_pymsg, "a");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->a = (Py_True == field);
    Py_DECREF(field);
  }
  {  // b
    PyObject * field = PyObject_GetAttrString(_pymsg, "b");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->b = (Py_True == field);
    Py_DECREF(field);
  }
  {  // x
    PyObject * field = PyObject_GetAttrString(_pymsg, "x");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->x = (Py_True == field);
    Py_DECREF(field);
  }
  {  // y
    PyObject * field = PyObject_GetAttrString(_pymsg, "y");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->y = (Py_True == field);
    Py_DECREF(field);
  }
  {  // l1
    PyObject * field = PyObject_GetAttrString(_pymsg, "l1");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->l1 = (Py_True == field);
    Py_DECREF(field);
  }
  {  // r1
    PyObject * field = PyObject_GetAttrString(_pymsg, "r1");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->r1 = (Py_True == field);
    Py_DECREF(field);
  }
  {  // l3
    PyObject * field = PyObject_GetAttrString(_pymsg, "l3");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->l3 = (Py_True == field);
    Py_DECREF(field);
  }
  {  // r3
    PyObject * field = PyObject_GetAttrString(_pymsg, "r3");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->r3 = (Py_True == field);
    Py_DECREF(field);
  }
  {  // select
    PyObject * field = PyObject_GetAttrString(_pymsg, "select");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->select = (Py_True == field);
    Py_DECREF(field);
  }
  {  // start
    PyObject * field = PyObject_GetAttrString(_pymsg, "start");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->start = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * my_joystick_msgs__msg__joystick__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Joystick */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("my_joystick_msgs.msg._joystick");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Joystick");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  my_joystick_msgs__msg__Joystick * ros_message = (my_joystick_msgs__msg__Joystick *)raw_ros_message;
  {  // lx
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->lx);
    {
      int rc = PyObject_SetAttrString(_pymessage, "lx", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ly
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->ly);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ly", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // rx
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->rx);
    {
      int rc = PyObject_SetAttrString(_pymessage, "rx", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ry
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->ry);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ry", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // dx
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->dx);
    {
      int rc = PyObject_SetAttrString(_pymessage, "dx", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // dy
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->dy);
    {
      int rc = PyObject_SetAttrString(_pymessage, "dy", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // l2
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->l2);
    {
      int rc = PyObject_SetAttrString(_pymessage, "l2", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // r2
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->r2);
    {
      int rc = PyObject_SetAttrString(_pymessage, "r2", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // a
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->a ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "a", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // b
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->b ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "b", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // x
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->x ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // y
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->y ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // l1
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->l1 ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "l1", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // r1
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->r1 ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "r1", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // l3
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->l3 ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "l3", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // r3
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->r3 ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "r3", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // select
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->select ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "select", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // start
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->start ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "start", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
