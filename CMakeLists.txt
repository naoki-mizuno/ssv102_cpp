cmake_minimum_required(VERSION 2.8.3)
project(ssv102)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

find_package(catkin REQUIRED COMPONENTS
    roscpp
    nmea_navsat_driver
    nmea_msgs
    serial
    )

find_package(Boost REQUIRED COMPONENTS system)

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES ssv102
    CATKIN_DEPENDS roscpp nmea_navsat_driver nmea_msgs serial
    )

include_directories(
    ${catkin_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include
    )

add_library(
    ssv102
    src/ssv102.cpp
    )

add_executable(
    ssv102_node
    src/ssv102_node.cpp
    )

target_link_libraries(ssv102_node
    ssv102
    ${catkin_LIBRARIES}
    ${Boost_SYSTEM_LIBRARY}
    )

install(TARGETS ssv102_node
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
    )
