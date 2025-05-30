cmake_minimum_required(VERSION 3.16)
project(Coup LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    MainWindow.cpp
    GameWindow.cpp
    Roles.cpp
    Game.cpp
    Player.cpp
)
add_executable(Coup ${SOURCES})

add_executable(CoupTests
    Test.cpp
    Roles.cpp
    Game.cpp
    Player.cpp
)
target_include_directories(CoupTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
add_test(NAME CoupTests COMMAND CoupTests)

add_custom_target(test
    COMMAND CoupTests
    DEPENDS CoupTests
    COMMENT "Building and running unit tests"
)

add_custom_target(valgrind
    COMMAND valgrind --leak-check=full $<TARGET_FILE:Coup>
    DEPENDS Coup
    COMMENT "Running Coup under Valgrind"
)

target_link_libraries(Coup PRIVATE Qt6::Widgets)
target_link_libraries(CoupTests PRIVATE Qt6::Widgets)
