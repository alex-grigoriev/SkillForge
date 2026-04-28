cmake_minimum_required(VERSION 3.16)

add_executable(Fishing main.cpp ${MY_INCLUDE_DIR}/Fishing.h Fishing.cpp)
target_include_directories(Fishing PUBLIC ${MY_INCLUDE_DIR})