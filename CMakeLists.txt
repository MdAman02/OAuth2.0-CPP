cmake_minimum_required(VERSION 3.21)
project(OAuth2_0_CPP)

set(CMAKE_CXX_STANDARD 11)

include_directories(
  "${CMAKE_SOURCE_DIR}/Repository"
  "${CMAKE_SOURCE_DIR}/includes"
)
add_library(OAuth2_0_CPP SHARED library.cpp)