cmake_minimum_required(VERSION 3.15)
project(GomoryHu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")


add_executable(GomoryHu main.cpp GomoryHuTree.h MinCuts/MinCutFunc.h MinCuts/FordFulkerson.cpp MinCuts/FordFulkerson.h GomoryHuTree.cpp utils.h MinCuts/PushRelabel.cpp MinCuts/PushRelabel.h MinCuts/Dinics.cpp MinCuts/Dinics.h GusfieldCutTree.cpp GusfieldCutTree.h ErdosRenyiModel.cpp WattsStrogatz.h)
add_subdirectory(GTest)