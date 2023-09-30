cmake_minimum_required(VERSION 3.17)
project(gatorAVL)

set(CMAKE_CXX_STANDARD 14)

add_executable(gatorAVL main.cpp AVLTree.cpp AVLTree.h Node.h)