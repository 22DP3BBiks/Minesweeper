cmake_minimum_required(VERSION 3.23)
project(mineswepper)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Os -static-libstdc++)
add_executable(mineswepper main.cpp)
