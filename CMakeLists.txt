cmake_minimum_required(VERSION 2.8.7)
project(darwin_diversions CXX)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Debug")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -O3")

include_directories("${CMAKE_SOURCE_DIR}/src")

file(GLOB_RECURSE darwin_diversions_SRC
   "src/*.cc"
)

add_library(darwin_diversions ${darwin_diversions_SRC})
