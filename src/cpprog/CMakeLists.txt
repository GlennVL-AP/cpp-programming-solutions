set(cpprog_VERSION "${${CMAKE_PROJECT_NAME}_VERSION}")
set(cpprog_VERSION_MAJOR "${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}")
set(cpprog_VERSION_MINOR "${${CMAKE_PROJECT_NAME}_VERSION_MINOR}")
set(cpprog_VERSION_PATCH "${${CMAKE_PROJECT_NAME}_VERSION_PATCH}")

if(NOT cpprog_VERSION_MAJOR)
    set(cpprog_VERSION_MAJOR 0)
endif()
if(NOT cpprog_VERSION_MINOR)
    set(cpprog_VERSION_MINOR 0)
endif()
if(NOT cpprog_VERSION_PATCH)
    set(cpprog_VERSION_PATCH 0)
endif()

# TODO this only updates the commit hash when the project is reconfigured
set(cpprog_GIT_COMMIT_HASH "")
execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    OUTPUT_VARIABLE cpprog_GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)

configure_file("${CMAKE_CURRENT_LIST_DIR}/cpprog_version.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/cpprog_version.cpp")

cpprog_add_library(
    TARGET cpprog
    CXX_MODULES
    "cpprog.cpp"
    "cpprog_utils.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/cpprog_version.cpp"
)
