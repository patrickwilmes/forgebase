cmake_minimum_required(VERSION 3.29)
project(forgebase)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(AK)
add_subdirectory(Libraries)
add_subdirectory(Forgebase)
add_subdirectory(Userland)
