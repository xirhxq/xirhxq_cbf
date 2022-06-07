cmake_minimum_required(VERSION 3.17)
project(cpp_V1_0)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_V1_0 cpp_file/main.cpp
        cpp_file/XIRHXQ_Point.cpp cpp_file/XIRHXQ_Line.cpp
        cpp_file/XIRHXQ_Polygon.cpp cpp_file/XIRHXQ_CVT.cpp
        cpp_file/XIRHXQ_Robot.cpp cpp_file/XIRHXQ_Swarm.cpp)