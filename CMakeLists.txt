cmake_minimum_required(VERSION 3.9)
project(homography)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(homography main.cpp MappedImage.h Plan.h utils.h)
target_link_libraries(homography ${OpenCV_LIBRARIES})