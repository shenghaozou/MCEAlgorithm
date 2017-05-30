cmake_minimum_required(VERSION 3.6)
project(Grad)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES common.h graph.h BK.h graph.cpp main.cpp BK.cpp MCE.cpp MCE.h BKz.cpp BKz.h BKz2.cpp BKz2.h BKz3.cpp BKz3.h experiment.cpp experiment.h sat.cpp sat.h BKz4.cpp BKz4.h common.cpp BKz5.cpp BKz5.h BKz6.cpp BKz6.h BKz7.cpp BKz7.h BKz8.cpp BKz8.h)
add_executable(Grad ${SOURCE_FILES})