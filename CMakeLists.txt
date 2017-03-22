cmake_minimum_required(VERSION 3.6)
project(Grad)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES common.h graph.h BK.h graph.cpp main.cpp BK.cpp MCE.cpp MCE.h BKz.cpp BKz.h BKz2.cpp BKz2.h)
add_executable(Grad ${SOURCE_FILES})