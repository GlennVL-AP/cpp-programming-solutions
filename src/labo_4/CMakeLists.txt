cpprog_add_library(TARGET datetime CXX_MODULES "datetime.cpp")

cpprog_add_executable(TARGET labo_4_ex_1 CXX_SOURCES ex_1.cpp DEPENDENCIES datetime)
cpprog_add_executable(TARGET labo_4_ex_2 CXX_SOURCES ex_2.cpp DEPENDENCIES datetime)
cpprog_add_executable(TARGET labo_4_ex_3 CXX_SOURCES ex_3.cpp DEPENDENCIES datetime)
cpprog_add_executable(TARGET labo_4_ex_4 CXX_SOURCES ex_4.cpp DEPENDENCIES datetime)
