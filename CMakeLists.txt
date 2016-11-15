cmake_minimum_required(VERSION 2.8.7)
project(darwin_diversions C CXX)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "No build type selected, default to Debug")
  set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -O3")

file(GLOB_RECURSE dd_HEADERS "src/*.h")

set (dd_INCLUDE_DIRS "")
foreach (_headerFile ${dd_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND dd_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES dd_INCLUDE_DIRS)

include_directories(${dd_INCLUDE_DIRS})

file(GLOB dd_SRC
   "src/*.cc"
   "src/*.c"
)

if (NOT DEFINED IOS_PLATFORM)
    file(GLOB dd_arch_specific_SRC
        "src/x86_64/*.cc"
    )
else()
    file(GLOB dd_arch_specific_SRC
        "src/ARMv7/*.cc"
        "src/AArch64/*.cc"
    )
endif()

file(GLOB dd_test_SRC
        "tests/*.cc"
)

add_library(darwin_diversions STATIC ${dd_SRC} ${dd_arch_specific_SRC})

add_executable(dd_tests ${dd_test_SRC})

target_link_libraries(dd_tests darwin_diversions "-framework CoreFoundation -framework Security")
