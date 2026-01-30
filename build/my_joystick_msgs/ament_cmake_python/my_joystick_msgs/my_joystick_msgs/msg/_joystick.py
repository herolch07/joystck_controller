# generated from rosidl_generator_py/resource/_idl.py.em
# with input from my_joystick_msgs:msg/Joystick.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Joystick(type):
    """Metaclass of message 'Joystick'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('my_joystick_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'my_joystick_msgs.msg.Joystick')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__joystick
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__joystick
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__joystick
            cls._TYPE_SUPPORT = module.type_support_msg__msg__joystick
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__joystick

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Joystick(metaclass=Metaclass_Joystick):
    """Message class 'Joystick'."""

    __slots__ = [
        '_lx',
        '_ly',
        '_rx',
        '_ry',
        '_dx',
        '_dy',
        '_l2',
        '_r2',
        '_a',
        '_b',
        '_x',
        '_y',
        '_l1',
        '_r1',
        '_l3',
        '_r3',
        '_select',
        '_start',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'lx': 'float',
        'ly': 'float',
        'rx': 'float',
        'ry': 'float',
        'dx': 'float',
        'dy': 'float',
        'l2': 'float',
        'r2': 'float',
        'a': 'boolean',
        'b': 'boolean',
        'x': 'boolean',
        'y': 'boolean',
        'l1': 'boolean',
        'r1': 'boolean',
        'l3': 'boolean',
        'r3': 'boolean',
        'select': 'boolean',
        'start': 'boolean',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.lx = kwargs.get('lx', float())
        self.ly = kwargs.get('ly', float())
        self.rx = kwargs.get('rx', float())
        self.ry = kwargs.get('ry', float())
        self.dx = kwargs.get('dx', float())
        self.dy = kwargs.get('dy', float())
        self.l2 = kwargs.get('l2', float())
        self.r2 = kwargs.get('r2', float())
        self.a = kwargs.get('a', bool())
        self.b = kwargs.get('b', bool())
        self.x = kwargs.get('x', bool())
        self.y = kwargs.get('y', bool())
        self.l1 = kwargs.get('l1', bool())
        self.r1 = kwargs.get('r1', bool())
        self.l3 = kwargs.get('l3', bool())
        self.r3 = kwargs.get('r3', bool())
        self.select = kwargs.get('select', bool())
        self.start = kwargs.get('start', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.lx != other.lx:
            return False
        if self.ly != other.ly:
            return False
        if self.rx != other.rx:
            return False
        if self.ry != other.ry:
            return False
        if self.dx != other.dx:
            return False
        if self.dy != other.dy:
            return False
        if self.l2 != other.l2:
            return False
        if self.r2 != other.r2:
            return False
        if self.a != other.a:
            return False
        if self.b != other.b:
            return False
        if self.x != other.x:
            return False
        if self.y != other.y:
            return False
        if self.l1 != other.l1:
            return False
        if self.r1 != other.r1:
            return False
        if self.l3 != other.l3:
            return False
        if self.r3 != other.r3:
            return False
        if self.select != other.select:
            return False
        if self.start != other.start:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def lx(self):
        """Message field 'lx'."""
        return self._lx

    @lx.setter
    def lx(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'lx' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'lx' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._lx = value

    @builtins.property
    def ly(self):
        """Message field 'ly'."""
        return self._ly

    @ly.setter
    def ly(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'ly' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'ly' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._ly = value

    @builtins.property
    def rx(self):
        """Message field 'rx'."""
        return self._rx

    @rx.setter
    def rx(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'rx' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'rx' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._rx = value

    @builtins.property
    def ry(self):
        """Message field 'ry'."""
        return self._ry

    @ry.setter
    def ry(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'ry' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'ry' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._ry = value

    @builtins.property
    def dx(self):
        """Message field 'dx'."""
        return self._dx

    @dx.setter
    def dx(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'dx' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'dx' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._dx = value

    @builtins.property
    def dy(self):
        """Message field 'dy'."""
        return self._dy

    @dy.setter
    def dy(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'dy' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'dy' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._dy = value

    @builtins.property
    def l2(self):
        """Message field 'l2'."""
        return self._l2

    @l2.setter
    def l2(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'l2' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'l2' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._l2 = value

    @builtins.property
    def r2(self):
        """Message field 'r2'."""
        return self._r2

    @r2.setter
    def r2(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'r2' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'r2' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._r2 = value

    @builtins.property
    def a(self):
        """Message field 'a'."""
        return self._a

    @a.setter
    def a(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'a' field must be of type 'bool'"
        self._a = value

    @builtins.property
    def b(self):
        """Message field 'b'."""
        return self._b

    @b.setter
    def b(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'b' field must be of type 'bool'"
        self._b = value

    @builtins.property
    def x(self):
        """Message field 'x'."""
        return self._x

    @x.setter
    def x(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'x' field must be of type 'bool'"
        self._x = value

    @builtins.property
    def y(self):
        """Message field 'y'."""
        return self._y

    @y.setter
    def y(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'y' field must be of type 'bool'"
        self._y = value

    @builtins.property
    def l1(self):
        """Message field 'l1'."""
        return self._l1

    @l1.setter
    def l1(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'l1' field must be of type 'bool'"
        self._l1 = value

    @builtins.property
    def r1(self):
        """Message field 'r1'."""
        return self._r1

    @r1.setter
    def r1(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'r1' field must be of type 'bool'"
        self._r1 = value

    @builtins.property
    def l3(self):
        """Message field 'l3'."""
        return self._l3

    @l3.setter
    def l3(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'l3' field must be of type 'bool'"
        self._l3 = value

    @builtins.property
    def r3(self):
        """Message field 'r3'."""
        return self._r3

    @r3.setter
    def r3(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'r3' field must be of type 'bool'"
        self._r3 = value

    @builtins.property
    def select(self):
        """Message field 'select'."""
        return self._select

    @select.setter
    def select(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'select' field must be of type 'bool'"
        self._select = value

    @builtins.property
    def start(self):
        """Message field 'start'."""
        return self._start

    @start.setter
    def start(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'start' field must be of type 'bool'"
        self._start = value
