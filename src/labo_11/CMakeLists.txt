cpprog_add_library(TARGET labo_11_lib CXX_SOURCES "libhello/hello.c" CXX_HEADERS "libhello/hello.h")
cpprog_add_executable(TARGET labo_11_hello CXX_SOURCES "main.c" DEPENDENCIES labo_11_lib)
