cmake_minimum_required(VERSION 2.8.0)

project(multi_thread)

add_executable(multi_thread_print multi_thread_print.cc)
add_executable(condition_variable condition_variable.cc)

target_link_libraries(multi_thread_print pthread)
target_link_libraries(condition_variable pthread)

