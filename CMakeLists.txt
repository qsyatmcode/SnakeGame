cmake_minimum_required(VERSION 3.27)
project(Snake)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)


add_executable(Snake src/main.cpp
        src/Drawer.h
        src/SnakePart.h
        src/Drawer.cpp
        src/Snake.h
        src/SnakePart.cpp
        src/Input.h
)
