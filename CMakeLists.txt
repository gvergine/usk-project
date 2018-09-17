cmake_minimum_required(VERSION 3.5)
project (usk-project)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -pedantic")

add_subdirectory(usk)
add_subdirectory(plugins)
