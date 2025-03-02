cpprog_add_library(TARGET datetime CXX_MODULES "datetime.cpp")
cpprog_add_executable(TARGET labo_4_ex_1 CXX_SOURCES ex_1.cpp DEPENDENCIES datetime)
