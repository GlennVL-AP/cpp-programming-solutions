find_package(Catch2 CONFIG REQUIRED)
include(Catch)

cpprog_add_test(TARGET test_cpprog CXX_SOURCES "cpprog.test.cpp")
