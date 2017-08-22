cmake_minimum_required(VERSION 2.6)
project(lift3)

add_executable(lift3 main.cpp)

install(TARGETS lift3 RUNTIME DESTINATION bin)

find_package (Threads)
target_link_libraries (lift3 ${CMAKE_THREAD_LIBS_INIT})
