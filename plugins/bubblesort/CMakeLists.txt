include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(bubblesort SHARED bubblesort.c)
set_property(TARGET bubblesort PROPERTY C_STANDARD 11)
target_link_libraries(bubblesort)
