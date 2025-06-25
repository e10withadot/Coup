cmake_minimum_required(VERSION 3.16)
project(Coup LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

set(SOURCES
    main.cpp
    MainWindow.cpp
    GameWindow.cpp
    Roles.cpp
    Game.cpp
    Player.cpp
)

qt_add_executable(Coup ${SOURCES})

target_link_libraries(Coup PRIVATE Qt6::Widgets)
