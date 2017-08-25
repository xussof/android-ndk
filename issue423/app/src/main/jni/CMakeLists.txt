cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

get_filename_component(PROJ_ROOT ${CMAKE_SOURCE_DIR}/../../../.. ABSOLUTE)
include_directories(${PROJ_ROOT}/jnilib/src/main/cpp/src)

get_filename_component(
    distribution_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../distribution
    ABSOLUTE)

add_library(lib_jniLib SHARED IMPORTED)
set_target_properties(lib_jniLib PROPERTIES IMPORTED_LOCATION
    ${distribution_DIR}/jniLib/${ANDROID_ABI}/libjniLib.so)

add_library(demoApp SHARED mainactivity.cpp)
target_link_libraries(demoApp lib_jniLib android log)

