include_guard()

macro(cpprog_init)
    _cpprog_generate_compile_commands()
    _cpprog_enable_modules()
    _cpprog_set_cxx_standard()
    _cpprog_enable_lto()
    _cpprog_find_clang_tidy()
    _cpprog_generate_gdbinit()
endmacro()

macro(_cpprog_generate_compile_commands)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endmacro()

macro(_cpprog_enable_modules)
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT clang)
    set(CMAKE_CXX_MODULE_STD ON)
    set(CMAKE_CXX_SCAN_FOR_MODULES ON)
endmacro()

macro(_cpprog_set_cxx_standard)
    set(CMAKE_CXX_STANDARD 26)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endmacro()

macro(_cpprog_enable_lto)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO ON)
endmacro()

macro(_cpprog_find_clang_tidy)
    find_program(CLANG_TIDY NAMES clang-tidy REQUIRED)
endmacro()

macro(_cpprog_generate_gdbinit)
    configure_file(${CMAKE_SOURCE_DIR}/gdbinit.in ${CMAKE_SOURCE_DIR}/.gdbinit)
endmacro()

function(cpprog_add_executable)
    set(options)
    set(oneValueArgs TARGET CXX_SOURCES)
    set(multiValueArgs CXX_MODULES DEPENDENCIES)
    cmake_parse_arguments(PARSE_ARGV 0 arg "${OPTIONS}" "${oneValueArgs}" "${multiValueArgs}")

    if(NOT arg_TARGET)
        message(FATAL_ERROR "Missing argument TARGET. Executable name is required!")
    endif()
    if(NOT arg_CXX_SOURCES)
        message(FATAL_ERROR "Missing argument CXX_SOURCES. At least a source file with main function is required!")
    endif()

    list(APPEND arg_DEPENDENCIES cpprog)

    add_executable(${arg_TARGET})
    target_sources(${arg_TARGET} PRIVATE FILE_SET CXX_MODULES FILES ${arg_CXX_MODULES} PRIVATE ${arg_CXX_SOURCES})
    target_link_libraries(${arg_TARGET} PRIVATE ${arg_DEPENDENCIES})
    _cpprog_set_compiler_options(TARGET ${arg_TARGET})
    _cpprog_enable_clangtidy(TARGET ${arg_TARGET} DEPENDENCIES ${arg_DEPENDENCIES})
endfunction()

function(cpprog_add_library)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs CXX_MODULES DEPENDENCIES)
    cmake_parse_arguments(PARSE_ARGV 0 arg "${OPTIONS}" "${oneValueArgs}" "${multiValueArgs}")

    if(NOT arg_TARGET)
        message(FATAL_ERROR "Missing argument TARGET. Library name is required!")
    endif()
    if (NOT arg_CXX_MODULES)
        message(FATAL_ERROR "Missing argument CXX_MODULES. At least one module is required!")
    endif()

    if(NOT "${arg_TARGET}" STREQUAL "cpprog")
        list(APPEND arg_DEPENDENCIES cpprog)
    endif()

    add_library(${arg_TARGET})
    target_sources(${arg_TARGET} PUBLIC FILE_SET CXX_MODULES FILES ${arg_CXX_MODULES})
    target_link_libraries(${arg_TARGET} PRIVATE ${arg_DEPENDENCIES})
    _cpprog_set_compiler_options(TARGET ${arg_TARGET})
    _cpprog_enable_clangtidy(TARGET ${arg_TARGET} DEPENDENCIES ${arg_DEPENDENCIES})
endfunction()

function(_cpprog_set_compiler_options)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs)
    cmake_parse_arguments(PARSE_ARGV 0 arg "${OPTIONS}" "${oneValueArgs}" "${multiValueArgs}")

    target_compile_options(${arg_TARGET} PRIVATE
        "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=/project_root"
        "-Wall;-Wextra;-Wpedantic;-Wshadow;-Wconversion;-Wsign-conversion;-Wdouble-promotion;-Wextra-semi;-Wnon-virtual-dtor"
        "-Wold-style-cast;-Wcast-align;-Wunused;-Woverloaded-virtual;-Wnull-dereference;-Wimplicit-fallthrough;-Wformat=2"
        "-Werror"
    )
endfunction()

function(_cpprog_enable_clangtidy)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs DEPENDENCIES)
    cmake_parse_arguments(PARSE_ARGV 0 arg "${OPTIONS}" "${oneValueArgs}" "${multiValueArgs}")

    get_target_property(cpprog_CXX_STANDARD ${arg_TARGET} CXX_STANDARD)

    set(cpprog_CLANG_TIDY
        ${CLANG_TIDY}
        --extra-arg=-fprebuilt-module-path=${CMAKE_BINARY_DIR}/CMakeFiles/__cmake_cxx${cpprog_CXX_STANDARD}.dir
        --extra-arg=-fprebuilt-module-path=${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${arg_TARGET}.dir
    )

    foreach(cpprog_DEP IN LISTS arg_DEPENDENCIES)
        get_target_property(cpprog_DEP_DIR ${cpprog_DEP} BINARY_DIR)
        list(APPEND cpprog_CLANG_TIDY --extra-arg=-fprebuilt-module-path=${cpprog_DEP_DIR}/CMakeFiles/${cpprog_DEP}.dir)
    endforeach()

    set_target_properties(${arg_TARGET} PROPERTIES CXX_CLANG_TIDY "${cpprog_CLANG_TIDY}")
endfunction()
