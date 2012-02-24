CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(aiclass)

FIND_PACKAGE(Boost 1.42 REQUIRED)
include_directories(${BOOST_INCLUDE_DIR})

ADD_EXECUTABLE(aiRotCypher rotation_cypher.cpp)

ADD_EXECUTABLE(aiColumnOrder column_order.cpp)

