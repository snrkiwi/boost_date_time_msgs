cmake_minimum_required(VERSION 2.8.3)
project(boost_date_time_msgs)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  message_generation
  std_msgs
)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS date_time)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  Ptime.msg
  TimeDuration.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS std_msgs message_runtime
)

###########
## Build ##
###########

## Language: cpp
if(TARGET ${PROJECT_NAME}_generate_messages_cpp)
  ## Overwrite generated header files in devel-space
  file(GLOB HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/*.h"
  )
  configure_file(cmake/rename_generated_header_files.cmake.in cmake/rename_generated_header_files.cmake @ONLY)
  add_custom_target(${PROJECT_NAME}_rename_generated_header_files
    DEPENDS ${HEADERS}
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake/rename_generated_header_files.cmake
    COMMENT "Moving generated C++ header files to include/${PROJECT_NAME}/generated/."
  )
  add_dependencies(${PROJECT_NAME}_rename_generated_header_files ${PROJECT_NAME}_generate_messages_cpp)
  add_dependencies(${PROJECT_NAME}_generate_messages ${PROJECT_NAME}_rename_generated_header_files)
endif()

## Language: Python
# TODO

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark cpp header files for installation
install(DIRECTORY
  include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)
install(DIRECTORY include/${PROJECT_NAME}
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)
