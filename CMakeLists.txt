cmake_minimum_required(VERSION 3.16)
project(Coup LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    MainWindow.cpp
    Roles.cpp
    Game.cpp
    Player.cpp
)

add_executable(Coup ${SOURCES})
target_link_libraries(Coup PRIVATE Qt6::Widgets)
