include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(usk-shell SHARED shell.c strsplit.c)
set_property(TARGET usk-shell PROPERTY C_STANDARD 11)
target_link_libraries(usk-shell readline)
