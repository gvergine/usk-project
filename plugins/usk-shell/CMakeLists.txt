include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(usk-shell SHARED shell.c strsplit.c)
target_link_libraries(usk-shell readline)
