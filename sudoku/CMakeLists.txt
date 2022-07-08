cmake_minimum_required(VERSION 3.16.0)
project(sudoku VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

# Catch2
Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2.git
    GIT_TAG         v2.13.9 
)
FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/contrib/)

# Sudoku
set(HEADERS_SUDOKU include/sudoku/casilla.hpp include/sudoku/sudoku.hpp include/sudoku/casilla.hpp)
set(SOURCE_SUDOKU src/casilla.cpp src/sudoku.cpp)

add_executable(sudoku main.cpp ${SOURCE_SUDOKU} ${HEADERS_SUDOKU})
target_include_directories(sudoku PRIVATE include/)
target_link_options(sudoku PRIVATE /PROFILE)

# Pruebas
add_executable(pruebas_sudoku tests/pruebas_sudoku.cpp ${SOURCE_SUDOKU})
target_link_libraries(pruebas_sudoku PRIVATE Catch2::Catch2)
target_include_directories(pruebas_sudoku PRIVATE include/)

include(CTest)
include(Catch)
catch_discover_tests(pruebas_sudoku)
