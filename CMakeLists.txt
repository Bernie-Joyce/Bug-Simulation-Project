cmake_minimum_required(VERSION 4.1)
project(A_Bugs_Life)

set(CMAKE_CXX_STANDARD 20)

add_executable(A_Bugs_Life main.cpp
        Bugs/Bug.h
        Bugs/Crawler.h
        Bugs/Crawler.cpp
        Bugs/Bug.cpp
        Bugs/Hopper.h
        Bugs/Hopper.cpp
        Board/Board.h
        Board/Board.cpp)
