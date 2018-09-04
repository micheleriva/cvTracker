cmake_minimum_required(VERSION 3.12)
project(cvTracker)

set(CMAKE_CXX_STANDARD 14)

add_executable(cvTracker main.cpp src/constants.h src/motion-detector.h src/motion-detector-internal.h src/utility.h)