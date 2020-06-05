cmake_minimum_required(VERSION 3.15)
project(GomoryHu)

set(CMAKE_CXX_STANDARD 17)

add_executable(GomoryHu main.cpp GomoryHuTree.h MinCuts/MinCutFunc.h MinCuts/FordFulkerson.cpp MinCuts/FordFulkerson.h GomoryHuTree.cpp utils.h MinCuts/PushRelabel.cpp MinCuts/PushRelabel.h MinCuts/Dinics.cpp MinCuts/Dinics.h GusfieldCutTree.cpp GusfieldCutTree.h)
add_subdirectory(GTest)