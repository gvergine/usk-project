include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(bubblesort SHARED bubblesort.c)
target_link_libraries(bubblesort)
