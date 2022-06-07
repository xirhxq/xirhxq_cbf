cmake_minimum_required(VERSION 3.21)
project(V8_0)

set(CMAKE_CXX_STANDARD 14)

link_directories(/Library/gurobi951/macos_universal2/lib)
include_directories(/Library/gurobi951/macos_universal2/include)

add_executable(V8.0 XIRHXQ_cbf_main.cpp Robot.cpp First_Order_UGV.cpp
        computing_geometry/Point.cpp computing_geometry/Line.cpp computing_geometry/Polygon.cpp computing_geometry/CVT.cpp World.cpp
        Swarm.cpp Energy_CBF.cpp)
target_link_libraries(V8.0 libgurobi_c++.a libgurobi95.dylib)


add_executable(Gurobi_test Gurobi_test.cpp)
target_link_libraries(Gurobi_test libgurobi_c++.a libgurobi95.dylib)