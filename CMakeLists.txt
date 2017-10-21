cmake_minimum_required(VERSION 3.7)
project(laboratory_work_1_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp DataStructures.h MeshLoader.h AneuMeshLoader.cpp AneuMeshLoader.h MeshLoader.cpp DataStructures.cpp NeuMeshLoader.cpp NeuMeshLoader.h Exceptions.h)
add_executable(laboratory_work_1_2 ${SOURCE_FILES})