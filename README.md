# boost_date_time_msgs
Package designed to be able to nest boost::posix_time::ptime and boost::posix_time::time_duration in a ROS message. Implementation note: ptime is serialized as ros::Time and time_duration as ros::Duration.
