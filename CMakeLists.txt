cmake_minimum_required(VERSION 4.0 FATAL_ERROR)

include("${CMAKE_CURRENT_LIST_DIR}/cmake/cpprog.cmake")

cpprog_init()

project(CppProgLaboSolutions VERSION 0.0.1 LANGUAGES C CXX)

add_subdirectory(src)

include(CTest)
enable_testing()
add_subdirectory(tests)
