cmake_minimum_required(VERSION 3.8)
project(AVL)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp nodo.cpp nodo.h arbol.cpp arbol.h datafile.cpp datafile.h)
add_executable(AVL ${SOURCE_FILES})