// This header is used to teach ROS to transport boost::posix_time::time_duration
// using a standard std_msgs/Duration.msg


#ifndef BOOST_DATE_TIME_DATE_DURATION_H
#define BOOST_DATE_TIME_DATE_DURATION_H


#include <string>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>
#include <ros/static_assert.h> 

#include <std_msgs/Duration.h>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace boost_date_time_msgs 
{
template <typename ContainerAllocator> using TimeDuration_ = ::boost::posix_time::time_duration;
}  // namespace boost_date_time_msgs

namespace ros
{
namespace message_traits
{

template <>
struct IsFixedSize< ::boost::posix_time::time_duration >
  : TrueType
  { };

template <>
struct IsFixedSize< ::boost::posix_time::time_duration const>
  : TrueType
  { };

template <>
struct IsMessage< ::boost::posix_time::time_duration >
  : TrueType
  { };

template <>
struct IsMessage< ::boost::posix_time::time_duration const>
  : TrueType
  { };

template <>
struct HasHeader< ::boost::posix_time::time_duration >
  : FalseType
  { };

template <>
struct HasHeader< ::boost::posix_time::time_duration const>
  : FalseType
  { };

// An md5 sum is a hash: in ROS, it is used to verify that subscribers and publishers are 
// using exactly the same message definitions, i.e. the md5 sum is computed from message definition files.
// Here we set time_duration md5 sum to be the same as the ros::Duration md5 sum therefore a
// publisher can public a ros::Duration and a scubscriber can subscribe to the same topic using a 
// boost::posix_time::time_duration.
// Of course it is our rsponsibility to ensure that boost::posix_time::time_duration is serialized the same way
// of ros::Duration as it is done below.
template<>
struct MD5Sum< ::boost::posix_time::time_duration >
{
  static const char* value()
  {
    // Ensure that if the definition of std_msgs/Time changes we have a compile error here.
    ROS_STATIC_ASSERT(MD5Sum<::std_msgs::Duration>::static_value1 == 0x3e286caf4241d664ULL);
    ROS_STATIC_ASSERT(MD5Sum<::std_msgs::Duration>::static_value2 == 0xe55f3ad380e2ae46ULL);
    return MD5Sum<::std_msgs::Duration>::value();
  }

  static const char* value(const ::boost::posix_time::time_duration&)
  {
    return MD5Sum<::std_msgs::Duration>::value();
  }
};

template <>
struct DataType< ::boost::posix_time::time_duration >
{
  static const char* value()
  {
    return DataType<::std_msgs::Duration>::value();
  }

  static const char* value(const ::boost::posix_time::time_duration&)
  {
    return DataType<::std_msgs::Duration>::value();
  }
};

template <>
struct Definition< ::boost::posix_time::time_duration >
{
  static const char* value()
  {
    return Definition<::std_msgs::Duration>::value();
  }

  static const char* value(const ::boost::posix_time::time_duration&)
  {
    return Definition<::std_msgs::Duration>::value();
  }
};

} // namespace message_traits
} // namespace ros

// We serialize boost::posix_time::time_duration the same way of ros::Duration
namespace ros
{
namespace serialization
{

template<>
struct Serializer<::boost::posix_time::time_duration>
{
  template<typename Stream>
  inline static void write(Stream& stream, const ::boost::posix_time::time_duration& d)
  {
    ros::Duration tmp;
    tmp.sec = d.total_seconds();
#if defined(BOOST_DATE_TIME_HAS_NANOSECONDS) 
    tmp.nsec = d.fractional_seconds(); 
#else 
    #warning boost time uses only microseconds nanoseconds are lost 
    tmp.nsec = d.fractional_seconds()*1000; 
#endif 
    stream.next(tmp);
  }

  template<typename Stream>
  inline static void read(Stream& stream, ::boost::posix_time::time_duration& d)
  {
    ros::Duration tmp;
    
    stream.next(tmp);
    d = tmp.toBoost();
  }

  inline static uint32_t serializedLength(const ::boost::posix_time::time_duration&)
  {
    uint32_t size = 0;
    ros::Duration tmp;

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
struct Printer< ::boost::posix_time::time_duration >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::boost::posix_time::time_duration& d)
  {
    s << indent << to_simple_string(d) << std::endl;
  }
};

} // namespace message_operations
} // namespace ros

#endif // BOOST_DATE_TIME_PTIME_H
