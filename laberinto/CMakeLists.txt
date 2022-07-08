cmake_minimum_required(VERSION 3.0.0)
project(laberinto-perfecto VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

add_executable(laberinto-perfecto main.cpp src/modelo.cpp)
target_include_directories(laberinto-perfecto PRIVATE include/)