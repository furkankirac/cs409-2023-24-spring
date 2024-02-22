cmake_minimum_required(VERSION 3.0)

project(advcpp)

SET(CMAKE_CXX_STANDARD 20)
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# added for MacOS Sonoma + GCC 13.2 installation's linker problems
# selects classic linker to be used, not the new linker
SET(CMAKE_CXX_FLAGS "-Wl,-ld_classic")

add_executable(w1a1 "week1-check-lms-for-introduction-ppt.cpp")
add_executable(w2a1 "week2-app1.cpp")
add_executable(w2a2 "week2-app2.cpp")
add_executable(w3a1 "week3-app1.cpp")
add_executable(w3a2 "week3-app2.cpp")
