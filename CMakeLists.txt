cmake_minimum_required(VERSION 3.10)
project(Calculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(calculator
    src/main.cpp
    src/sqlist.cpp
    src/linklist.cpp
    src/expression.cpp
    src/menu.cpp
    src/utils.cpp
    src/func.cpp
)
