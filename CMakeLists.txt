cmake_minimum_required(VERSION 3.16)

project(AoK VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_AUTOMOC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Boost REQUIRED COMPONENTS program_options)

include_directories(inc)

file(GLOB SOURCES "src/*.cpp")

QT5_WRAP_CPP(HDR_MOC "inc/GameWindow.hpp")
QT5_WRAP_CPP(HDR_MOC "inc/OperatorPanel.hpp")

add_executable(AoK ${SOURCES} ${HDR_MOC})

target_link_libraries(AoK PRIVATE Qt5::Widgets Qt5::Multimedia ${Boost_PROGRAM_OPTIONS_LIBRARY})