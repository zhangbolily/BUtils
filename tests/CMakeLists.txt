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

project (tests)

SET (EXECUTABLE_OUTPUT_PATH ${BUtils_BINARY_DIR}/bin)

include_directories ("${BUtils_BINARY_DIR}/third_party/googletest/googletest/include")

aux_source_directory (. DIR_TESTS_SRCS)
link_directories (${BUtils_BINARY_DIR})
add_executable (${PROJECT_NAME} ${DIR_TESTS_SRCS})
target_link_libraries (${PROJECT_NAME} butils gtest gtest_main pthread)
if (CODE_COVERAGE)
    add_test (NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
endif()
