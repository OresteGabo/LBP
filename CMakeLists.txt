cmake_minimum_required(VERSION 3.27)
project(TP_LBP)

set(CMAKE_CXX_STANDARD 17)

# Find the OpenCV package
find_package(OpenCV REQUIRED)

add_executable(TP_LBP main.cpp)

# Link OpenCV to your executable
target_link_libraries(TP_LBP ${OpenCV_LIBS})