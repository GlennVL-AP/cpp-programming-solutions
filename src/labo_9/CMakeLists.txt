cpprog_add_library(
    TARGET labo_9_lib
    CXX_MODULES
    "ex_1_vector.cpp"
)

cpprog_add_executable(TARGET labo_9_ex_1 CXX_SOURCES "ex_1_main.cpp" DEPENDENCIES labo_9_lib)
