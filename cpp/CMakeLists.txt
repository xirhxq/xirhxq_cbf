cmake_minimum_required(VERSION 3.17)
project(V4_0)

set(CMAKE_CXX_STANDARD 17)


add_executable(V4_0 main.cpp Point.cpp
        Line.cpp Polygon.cpp CVT.cpp
        Robot.cpp Swarm.cpp)