add_custom_target(
    generate_cpprog_version ALL
    COMMAND "${CMAKE_COMMAND}"
        -DPROJECT_ROOT="${CMAKE_SOURCE_DIR}"
        -DINPUT_FILE="${CMAKE_CURRENT_LIST_DIR}/cpprog_version.cpp.in"
        -DOUTPUT_FILE="${CMAKE_CURRENT_BINARY_DIR}/cpprog_version.cpp"
        -DVERSION_MAJOR="${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}"
        -DVERSION_MINOR="${${CMAKE_PROJECT_NAME}_VERSION_MINOR}"
        -DVERSION_PATCH="${${CMAKE_PROJECT_NAME}_VERSION_PATCH}"
        -P "${CMAKE_CURRENT_LIST_DIR}/generate_version_info.cmake"
    BYPRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/cpprog_version.cpp"
    COMMENT "[cpprog] Generating version info."
)

cpprog_add_library(
    TARGET cpprog
    CXX_MODULES
    "cpprog.cpp"
    "cpprog_utils.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/cpprog_version.cpp"
)

add_dependencies(cpprog generate_cpprog_version)
