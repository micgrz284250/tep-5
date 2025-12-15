cmake_minimum_required(VERSION 4.1)
project(tep_5)

set(CMAKE_CXX_STANDARD 11)

add_executable(tep_5 main.cpp
        my_smart_pointer.h
        ref_counter.h
        simple_testing_class.h
        tep_3/console.cpp
        tep_3/console.h
        tep_3/constants.h
        tep_3/parser.h
        tep_3/parser.cpp
        tep_3/tree.h
        tep_3/tree.cpp)
