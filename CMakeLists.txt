cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

include("${CMAKE_CURRENT_LIST_DIR}/cmake/cpprog.cmake")

cpprog_init()

project(CppProgLabo3 LANGUAGES CXX)

add_subdirectory(src)
