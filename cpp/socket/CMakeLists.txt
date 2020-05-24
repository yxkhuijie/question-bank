cmake_minimum_required(VERSION 2.8.0)

project(socket)

add_executable(socket_server socket_server.cc)
add_executable(socket_client socket_client.cc)

target_link_libraries(socket_server pthread)
target_link_libraries(socket_client pthread)
