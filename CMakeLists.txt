cmake_minimum_required(VERSION 3.17)

project(poker)

add_compile_options(-std=c++20)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB src ${CMAKE_SOURCE_DIR}/sources/*.cpp)
add_executable(${PROJECT_NAME} ${src})