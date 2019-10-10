// Generated by gencpp from file bebop_msgs/Ardrone3AntiflickeringStatemodeChanged.msg
// DO NOT EDIT!


#ifndef BEBOP_MSGS_MESSAGE_ARDRONE3ANTIFLICKERINGSTATEMODECHANGED_H
#define BEBOP_MSGS_MESSAGE_ARDRONE3ANTIFLICKERINGSTATEMODECHANGED_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace bebop_msgs
{
template <class ContainerAllocator>
struct Ardrone3AntiflickeringStatemodeChanged_
{
  typedef Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> Type;

  Ardrone3AntiflickeringStatemodeChanged_()
    : header()
    , mode(0)  {
    }
  Ardrone3AntiflickeringStatemodeChanged_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , mode(0)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef uint8_t _mode_type;
  _mode_type mode;



  enum {
    mode_auto = 0u,
    mode_FixedFiftyHertz = 1u,
    mode_FixedSixtyHertz = 2u,
  };


  typedef boost::shared_ptr< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> const> ConstPtr;

}; // struct Ardrone3AntiflickeringStatemodeChanged_

typedef ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<std::allocator<void> > Ardrone3AntiflickeringStatemodeChanged;

typedef boost::shared_ptr< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged > Ardrone3AntiflickeringStatemodeChangedPtr;
typedef boost::shared_ptr< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged const> Ardrone3AntiflickeringStatemodeChangedConstPtr;

// constants requiring out of line definition

   

   

   



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace bebop_msgs

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': False, 'IsMessage': True, 'HasHeader': True}
// {'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg'], 'bebop_msgs': ['/home/mlab/catkin_ws/src/bebop_autonomy/bebop_msgs/msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> >
{
  static const char* value()
  {
    return "949916415ccdcdf00022c85192c0ac67";
  }

  static const char* value(const ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x949916415ccdcdf0ULL;
  static const uint64_t static_value2 = 0x0022c85192c0ac67ULL;
};

template<class ContainerAllocator>
struct DataType< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> >
{
  static const char* value()
  {
    return "bebop_msgs/Ardrone3AntiflickeringStatemodeChanged";
  }

  static const char* value(const ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Ardrone3AntiflickeringStatemodeChanged\n\
# auto-generated from up stream XML files at\n\
#   github.com/Parrot-Developers/libARCommands/tree/master/Xml\n\
# To check upstream commit hash, refer to last_build_info file\n\
# Do not modify this file by hand. Check scripts/meta folder for generator files.\n\
#\n\
# SDK Comment: Antiflickering mode.\n\
\n\
Header header\n\
\n\
# Mode of the anti flickering functionnality\n\
uint8 mode_auto=0  # Anti flickering based on the electric frequency previously sent\n\
uint8 mode_FixedFiftyHertz=1  # Anti flickering based on a fixed frequency of 50Hz\n\
uint8 mode_FixedSixtyHertz=2  # Anti flickering based on a fixed frequency of 60Hz\n\
uint8 mode\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
";
  }

  static const char* value(const ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.mode);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct Ardrone3AntiflickeringStatemodeChanged_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::bebop_msgs::Ardrone3AntiflickeringStatemodeChanged_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "mode: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.mode);
  }
};

} // namespace message_operations
} // namespace ros

#endif // BEBOP_MSGS_MESSAGE_ARDRONE3ANTIFLICKERINGSTATEMODECHANGED_H
