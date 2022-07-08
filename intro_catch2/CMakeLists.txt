cmake_minimum_required(VERSION 3.16)
project(intro_catch2 VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

# add_subdirectory(libs/Catch2-2.x)
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.9
)
FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/contrib/")

# Pruebas
add_executable(test_factorial tests/test_factorial.cpp)
target_link_libraries(test_factorial PRIVATE Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(test_factorial)