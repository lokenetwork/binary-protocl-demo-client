cmake_minimum_required(VERSION 3.5)
project(tests)

set(CMAKE_C_FLAGS "-std=c99 -Wall")

set(SOURCE_FILES main.c)
add_executable(binary_protocol_client ${SOURCE_FILES})