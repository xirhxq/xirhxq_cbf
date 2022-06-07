cmake_minimum_required(VERSION 3.21)
project(V7_0)

set(CMAKE_CXX_STANDARD 14)

add_executable(test test.cpp Robot.cpp First_Order_UGV.cpp
        Point.cpp Line.cpp Polygon.cpp CVT.cpp World.cpp
        Swarm.cpp)

add_executable(V7.0 XIRHXQ_cbf_main.cpp Robot.cpp First_Order_UGV.cpp
        Point.cpp Line.cpp Polygon.cpp CVT.cpp World.cpp
        Swarm.cpp CBF.cpp Energy_CBF.cpp Energy_CBF.h)

add_executable(test_py test_py.cpp)