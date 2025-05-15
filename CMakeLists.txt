cmake_minimum_required(VERSION 3.10)
project(ian_counter LANGUAGES CXX)

# Require C++17 for std::filesystem, set to c++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ian_counter src/main.cpp)