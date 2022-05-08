cmake_minimum_required(VERSION 3.22)
project(project4)

set(CMAKE_CXX_STANDARD 14)

# Configure input file
set(file1 program4_test.txt)
configure_file(${file1} ${file1} COPYONLY)

add_executable(project4 prog4.cpp)
