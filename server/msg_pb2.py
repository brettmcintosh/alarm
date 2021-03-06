# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: msg.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='msg.proto',
  package='msg',
  syntax='proto3',
  serialized_pb=_b('\n\tmsg.proto\x12\x03msg\"\xd9\x01\n\x06Update\x12)\n\x0cservice_name\x18\x01 \x01(\x0e\x32\x13.msg.Update.Service\x12\"\n\x06status\x18\x02 \x01(\x0e\x32\x12.msg.Update.Status\"4\n\x07Service\x12\n\n\x06\x41RPING\x10\x00\x12\x08\n\x04\x44OOR\x10\x01\x12\x07\n\x03PIR\x10\x02\x12\n\n\x06\x43\x41MERA\x10\x03\"J\n\x06Status\x12\x06\n\x02OK\x10\x00\x12\x0b\n\x07TROUBLE\x10\x01\x12\t\n\x05\x41RMED\x10\x02\x12\x0c\n\x08\x44ISARMED\x10\x03\x12\x12\n\x0eMALFUNCTIONING\x10\x04\"t\n\x07\x43ommand\x12 \n\x07\x63ommand\x18\x01 \x01(\x0e\x32\x0f.msg.Command.Do\"G\n\x02\x44o\x12\x07\n\x03\x41RM\x10\x00\x12\n\n\x06\x44ISARM\x10\x01\x12\x10\n\x0cSTART_RECORD\x10\x02\x12\x0f\n\x0bSTOP_RECORD\x10\x03\x12\t\n\x05PANIC\x10\x04\x62\x06proto3')
)



_UPDATE_SERVICE = _descriptor.EnumDescriptor(
  name='Service',
  full_name='msg.Update.Service',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='ARPING', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DOOR', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PIR', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='CAMERA', index=3, number=3,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=108,
  serialized_end=160,
)
_sym_db.RegisterEnumDescriptor(_UPDATE_SERVICE)

_UPDATE_STATUS = _descriptor.EnumDescriptor(
  name='Status',
  full_name='msg.Update.Status',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='OK', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='TROUBLE', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='ARMED', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DISARMED', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MALFUNCTIONING', index=4, number=4,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=162,
  serialized_end=236,
)
_sym_db.RegisterEnumDescriptor(_UPDATE_STATUS)

_COMMAND_DO = _descriptor.EnumDescriptor(
  name='Do',
  full_name='msg.Command.Do',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='ARM', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='DISARM', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='START_RECORD', index=2, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='STOP_RECORD', index=3, number=3,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='PANIC', index=4, number=4,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=283,
  serialized_end=354,
)
_sym_db.RegisterEnumDescriptor(_COMMAND_DO)


_UPDATE = _descriptor.Descriptor(
  name='Update',
  full_name='msg.Update',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='service_name', full_name='msg.Update.service_name', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='status', full_name='msg.Update.status', index=1,
      number=2, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _UPDATE_SERVICE,
    _UPDATE_STATUS,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=19,
  serialized_end=236,
)


_COMMAND = _descriptor.Descriptor(
  name='Command',
  full_name='msg.Command',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='command', full_name='msg.Command.command', index=0,
      number=1, type=14, cpp_type=8, label=1,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
    _COMMAND_DO,
  ],
  options=None,
  is_extendable=False,
  syntax='proto3',
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=238,
  serialized_end=354,
)

_UPDATE.fields_by_name['service_name'].enum_type = _UPDATE_SERVICE
_UPDATE.fields_by_name['status'].enum_type = _UPDATE_STATUS
_UPDATE_SERVICE.containing_type = _UPDATE
_UPDATE_STATUS.containing_type = _UPDATE
_COMMAND.fields_by_name['command'].enum_type = _COMMAND_DO
_COMMAND_DO.containing_type = _COMMAND
DESCRIPTOR.message_types_by_name['Update'] = _UPDATE
DESCRIPTOR.message_types_by_name['Command'] = _COMMAND
_sym_db.RegisterFileDescriptor(DESCRIPTOR)

Update = _reflection.GeneratedProtocolMessageType('Update', (_message.Message,), dict(
  DESCRIPTOR = _UPDATE,
  __module__ = 'msg_pb2'
  # @@protoc_insertion_point(class_scope:msg.Update)
  ))
_sym_db.RegisterMessage(Update)

Command = _reflection.GeneratedProtocolMessageType('Command', (_message.Message,), dict(
  DESCRIPTOR = _COMMAND,
  __module__ = 'msg_pb2'
  # @@protoc_insertion_point(class_scope:msg.Command)
  ))
_sym_db.RegisterMessage(Command)


# @@protoc_insertion_point(module_scope)
