cmake_minimum_required(VERSION 4.1)
project(A_Bugs_Life)

set(CMAKE_CXX_STANDARD 20)

add_executable(A_Bugs_Life main.cpp
        Bug.h
        Crawler.h
        Crawler.cpp
        Bug.cpp
        Hopper.h
        Hopper.cpp
        FileReader.h
        FileReader.cpp
        Board.h
        Board.cpp)
