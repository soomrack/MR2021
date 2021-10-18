project(task02)


add_library(mylib static mylib.h)
target_link_libraries(main mylib)

add_executable(main main.c)
