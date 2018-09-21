cmake_minimum_required(VERSION 3.5)
project (usk-project)
set(C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")

add_subdirectory(usk)
add_subdirectory(plugins)
