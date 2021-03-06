# MIT License
# 
# Copyright (c) 2018 Ball Chang
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required (VERSION 2.8.12)
project (BUtils)

aux_source_directory (src/BUtils DIR_SRCS)
include_directories ("${PROJECT_SOURCE_DIR}/include")
include_directories ("third_party/BCore/include")

# Set build environment
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

if (UNIX)
    add_definitions (-DUNIX)
elseif (WIN32)
    add_definitions (-DWIN32)
    MESSAGE("Windows system is detected.")
    option (WINDOWS_STL_INCLUDE_DIR "Specify which directory contains the STL header files.")
    
    include_directories (${WINDOWS_STL_INCLUDE_DIR})
endif ()

if (CMAKE_BUILD_TYPE MATCHES "Debug" OR WITH_DEBUG)
    add_definitions (-D_B_DEBUG_)
endif ()

# Code Coverage Configuration
add_library(coverage_config INTERFACE)

option(CODE_COVERAGE "Enable coverage reporting" OFF)
if (CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Add required flags (GCC & LLVM/Clang)
    target_compile_options(coverage_config INTERFACE
            -O0        # no optimization
            -g         # generate debug info
            --coverage # sets all required flags
            )
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
        target_link_options(coverage_config INTERFACE --coverage)
    else ()
        target_link_libraries(coverage_config INTERFACE --coverage)
    endif ()
endif ()

option (BUILD_TESTING "Build the testing tree." OFF)
# Only build tests if we are the top-level project
# Allows this to be used by super projects with `add_subdirectory`
if (BUILD_TESTING AND (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
    enable_testing()
    # Build tests
    add_subdirectory (tests)
    # Build gtest for unit tests
    add_subdirectory (${CMAKE_SOURCE_DIR}/third_party/googletest/)
endif ()

# Build deb package
# Package file name prefix
set (CPACK_PACKAGE_NAME ${PROJECT_NAME})
set (CPACK_DEBIAN_PACKAGE_NAME ${PROJECT_NAME})
set (CPACK_GENERATOR "DEB")
set (CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")
set (MAJOR_VERSION 0)
set (MINOR_VERSION 2)
set (PATCH_VERSION 0)
set (CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
set (CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
set (CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
set (CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6), libstdc++6")
set (CPACK_PACKAGE_DESCRIPTION "The Core of every Ball Chang's project.")
set (CPACK_PACKAGE_CONTACT "zhangbolily@gmail.com")
set (CPACK_DEBIAN_PACKAGE_MAINTAINER "Ball Chang")
include(CPack)

if (UNIX)
    set (EXTRA_LIBS ${EXTRA_LIBS} rt)
endif ()
set (EXTRA_LIBS ${EXTRA_LIBS} pthread)
set (LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library (butils SHARED ${DIR_SRCS})
target_link_libraries (butils ${EXTRA_LIBS})
set_property (TARGET butils PROPERTY CXX_STANDARD 11)

# Set install files
install (TARGETS butils DESTINATION lib)

install (
    FILES
    "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/BTimer.h"
    "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/BTiming.h"
    "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/BUtils.h"
    "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/BTimer"
    "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/BTiming"
    "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/BUtils"
    DESTINATION include/${PROJECT_NAME}
)
