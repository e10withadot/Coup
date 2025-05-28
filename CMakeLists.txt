cmake_minimum_required(VERSION 3.16)
project(Coup LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Coup main.cpp)
target_link_libraries(Coup PRIVATE Qt6::Widgets)
