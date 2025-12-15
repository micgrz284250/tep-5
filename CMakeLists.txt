cmake_minimum_required(VERSION 4.1)
project(tep_5)

set(CMAKE_CXX_STANDARD 11)

add_executable(tep_5 main.cpp
        my_smart_pointer.h
        ref_counter.h
        simple_testing_class.h)
