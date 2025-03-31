cmake_minimum_required(VERSION 3.30)
project(ca3_a_bugs_life)

set(CMAKE_CXX_STANDARD 20)

add_executable(ca3_a_bugs_life main.cpp
        Crawler.cpp
        Crawler.h
        Board.h
        Board.cpp)
