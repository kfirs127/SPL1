cmake_minimum_required(VERSION 3.10)
project(SPL1)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(SPL1
        include/Agent.h
        include/Graph.h
        include/json.hpp
        include/Session.h
        include/Tree.h
        "source files/Agent.cpp"
        "source files/CycleTree.cpp"
        "source files/Graph.cpp"
        "source files/Json.cpp"
        "source files/MaxRankTree.cpp"
        "source files/RootTree.cpp"
        "source files/Session.cpp"
        "source files/Tree.cpp"
        main.cpp)
