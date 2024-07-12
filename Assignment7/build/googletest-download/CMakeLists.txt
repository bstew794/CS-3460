cmake_minimum_required(VERSION 3.12)

project(googletest-download NONE)

include(ExternalProject)

ExternalProject_Add(googletest
GIT_REPOSITORY    https://github.com/google/googletest.git
GIT_TAG           main
SOURCE_DIR        "C:/Users/bstew/Documents/CS/CS 3460/Assignment7/build/googletest-src"
BINARY_DIR        "C:/Users/bstew/Documents/CS/CS 3460/Assignment7/build/googletest-build"
CONFIGURE_COMMAND ""
BUILD_COMMAND     ""
INSTALL_COMMAND   ""
TEST_COMMAND      ""
)
