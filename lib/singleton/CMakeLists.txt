cmake_minimum_required(VERSION 3.16)

project(Singleton LANGUAGES CXX)

file(GLOB HPP_FILES "include/*.hpp")
file(GLOB CPP_FILES "src/*.cpp")

include_directories("./include")

add_library(${PROJECT_NAME} SHARED ${HPP_FILES} ${CPP_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC "./include")