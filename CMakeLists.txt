cmake_minimum_required(VERSION 3.10)
project(huffman)

set(CMAKE_CXX_STANDARD 14)

add_executable(huffman
        object.h object.cpp
        VSArray.h VSArray.cpp
        TreeNode.h TreeNode.cpp
        main.cpp
)