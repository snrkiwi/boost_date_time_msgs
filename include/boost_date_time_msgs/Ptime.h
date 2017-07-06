// This header is used to teach ROS to transport boost::posix_time::ptime
// using a standard std_msgs/Time.msg

#ifndef BOOST_DATE_TIME_PTIME_H
#define BOOST_DATE_TIME_PTIME_H


#include <string>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>
#include <ros/static_assert.h> 

#include <std_msgs/Time.h>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace boost_date_time_msgs 
{
template <typename ContainerAllocator> using Ptime_ = ::boost::posix_time::ptime;
}  // namespace boost_date_time_msgs

namespace ros
{
namespace message_traits
{

template <>
struct IsFixedSize< ::boost::posix_time::ptime >
  : TrueType
  { };

template <>
struct IsFixedSize< ::boost::posix_time::ptime const>
  : TrueType
  { };

template <>
struct IsMessage< ::boost::posix_time::ptime >
  : TrueType
  { };

template <>
struct IsMessage< ::boost::posix_time::ptime const>
  : TrueType
  { };

template <>
struct HasHeader< ::boost::posix_time::ptime >
  : FalseType
  { };

template <>
struct HasHeader< ::boost::posix_time::ptime const>
  : FalseType
  { };

// An md5 sum is a hash: in ROS, it is used to verify that subscribers and publishers are 
// using exactly the same message definitions, i.e. the md5 sum is computed from message definition files.
// Here we set ptime md5 sum to be the same as the ros::Time md5 sum therefore a
// publisher can public a ros::Time and a scubscriber can subscribe to the same topic using a 
// boost::posix_time::ptime.
// Of course it is our rsponsibility to ensure that boost::posix_time::ptime is serialized the same way
// of ros::Time as it is done below.
template <>
struct MD5Sum< ::boost::posix_time::ptime >
{
  static const char* value()
  {
    // Ensure that if the definition of std_msgs/Time changes we have a compile error here.
    ROS_STATIC_ASSERT(MD5Sum<std_msgs::Time>::static_value1 == 0xcd7166c74c552c31ULL);
    ROS_STATIC_ASSERT(MD5Sum<std_msgs::Time>::static_value2 == 0x1fbcc2fe5a7bc289ULL);
    return MD5Sum<std_msgs::Time>::value();
  }

  static const char* value(const ::boost::posix_time::ptime&)
  {
    return MD5Sum<std_msgs::Time>::value();
  }
};

template <>
struct DataType< ::boost::posix_time::ptime >
{
  static const char* value()
  {
    return DataType<std_msgs::Time>::value();
  }

  static const char* value(const ::boost::posix_time::ptime&)
  {
    return DataType<std_msgs::Time>::value();
  }
};

template <>
struct Definition< ::boost::posix_time::ptime >
{
  static const char* value()
  {
    return Definition<std_msgs::Time>::value();
  }

  static const char* value(const ::boost::posix_time::ptime&)
  {
    return Definition<std_msgs::Time>::value();
  }
};

} // namespace message_traits
} // namespace ros

// We serialize boost::posix_time::ptime the same way of ros::Time
namespace ros
{
namespace serialization
{

template<>
struct Serializer<::boost::posix_time::ptime>
{
  template<typename Stream>
  inline static void write(Stream& stream, const ::boost::posix_time::ptime& t)
  {
    stream.next(ros::Time::fromBoost(t));
  }

  template<typename Stream>
  inline static void read(Stream& stream, ::boost::posix_time::ptime& t)
  {
    ros::Time tmp;
    
    stream.next(tmp);
    t = tmp.toBoost();
  }

  inline static uint32_t serializedLength(const ::boost::posix_time::ptime& t)
  {
    uint32_t size = 0;
    ros::Time tmp;

    size += serializationLength(tmp);

    return size;
  }
};

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template <>
struct Printer< ::boost::posix_time::ptime >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::boost::posix_time::ptime& t)
  {
    s << indent << to_iso_string(t) << std::endl;
  }
};

} // namespace message_operations
} // namespace ros

#endif // BOOST_DATE_TIME_PTIME_H
