cmake_minimum_required(VERSION 3.0...3.20)

project(JSONHandler)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

file(GLOB CPP_FILES "src/*.cpp")
file(GLOB HPP_FILES "include/*.hpp")

add_library(${PROJECT_NAME} SHARED ${CPP_FILES} ${HPP_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Core Cipher Logger)
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_executable(${PROJECT_NAME}_TEST main.cpp)
target_link_libraries(${PROJECT_NAME}_TEST ${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core Cipher Logger)
