find_package(Catch2 CONFIG REQUIRED)
include(Catch)

cpprog_add_test(TARGET test_cpprog CXX_SOURCES "cpprog.test.cpp")
cpprog_add_test(TARGET test_datetime CXX_SOURCES "datetime.test.cpp" DEPENDENCIES datetime)
