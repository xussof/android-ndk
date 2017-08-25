#
# Copyright (C) 2016 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

get_filename_component(PROJ_ROOT ${CMAKE_SOURCE_DIR}/../../../.. ABSOLUTE)
include_directories(${PROJ_ROOT}/native/src/main/cpp/src)

get_filename_component(
    distribution_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../distribution
    ABSOLUTE)

add_library(lib_native SHARED IMPORTED)
set_target_properties(lib_native PROPERTIES IMPORTED_LOCATION
    ${distribution_DIR}/native/${ANDROID_ABI}/libnative.so)

# this module main lib...
add_library(jniLib SHARED src/jniLib.c)
target_link_libraries(jniLib lib_native android log)

# post copying...
set(targetFile ${distribution_DIR}/jniLib/${ANDROID_ABI})
add_custom_command(TARGET jniLib POST_BUILD
                   COMMAND "${CMAKE_COMMAND}" -E
                   copy "$<TARGET_FILE:jniLib>" "${targetFile}/$<TARGET_FILE_NAME:jniLib>"
                   COMMENT "Copying jniLib to output directory")