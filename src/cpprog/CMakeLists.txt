cpprog_add_library(
    TARGET cpprog
    CXX_MODULES
    "cpprog.cpp"
    "cpprog_utils.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/cpprog_version.cpp"
)

cpprog_generate_version_info(
    TARGET cpprog
    INPUT_FILE "cpprog_version.cpp.in"
    OUTPUT_FILE "cpprog_version.cpp"
)
