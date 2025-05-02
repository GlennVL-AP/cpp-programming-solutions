include_guard()

macro(cpprog_init)
    _cpprog_generate_compile_commands()
    _cpprog_enable_cxx_modules()
    _cpprog_set_language_standards()
    _cpprog_enable_lto()
    _cpprog_find_clang_tidy()
    _cpprog_generate_debuginit()
endmacro()

macro(_cpprog_generate_compile_commands)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    file(RELATIVE_PATH cpprog_RELATIVE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build" "${CMAKE_CURRENT_BINARY_DIR}")

    execute_process(
        COMMAND "${CMAKE_COMMAND}" -E create_symlink
                "${cpprog_RELATIVE_BINARY_DIR}/compile_commands.json"
                "compile_commands.json"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
        RESULT_VARIABLE cpprog_SYMLINK_RESULT
        OUTPUT_QUIET
        ERROR_QUIET
    )

    if(NOT cpprog_SYMLINK_RESULT EQUAL 0)
        message(WARNING "[cpprog] Failed to create symlink for ${cpprog_RELATIVE_BINARY_DIR}/compile_commands.json!")
    else()
        message(STATUS "[cpprog] Created symlink for ${cpprog_RELATIVE_BINARY_DIR}/compile_commands.json.")
    endif()
endmacro()

macro(_cpprog_enable_cxx_modules)
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")
    set(CMAKE_CXX_MODULE_STD ON)
endmacro()

macro(_cpprog_set_language_standards)
    set(CMAKE_C_STANDARD 23)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS OFF)
    set(CMAKE_CXX_STANDARD 26)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endmacro()

macro(_cpprog_enable_lto)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)
endmacro()

macro(_cpprog_find_clang_tidy)
    find_program(CLANG_TIDY NAMES clang-tidy REQUIRED)
endmacro()

function(_cpprog_generate_debuginit)
    configure_file("${CMAKE_SOURCE_DIR}/lldbinit.in" "${CMAKE_SOURCE_DIR}/.lldbinit")
endfunction()

function(cpprog_add_executable)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs CXX_MODULES CXX_SOURCES DEPENDENCIES)
    cmake_parse_arguments(PARSE_ARGV 0 arg "${OPTIONS}" "${oneValueArgs}" "${multiValueArgs}")

    if(NOT arg_TARGET)
        message(FATAL_ERROR "[cpprog] Missing argument TARGET. Executable name is required!")
    endif()
    if(NOT arg_CXX_SOURCES)
        message(FATAL_ERROR "[cpprog] Missing argument CXX_SOURCES. At least a source file with main function is required!")
    endif()

    list(LENGTH arg_CXX_SOURCES cpprog_NUM_SOURCES)
    if(cpprog_NUM_SOURCES GREATER 1)
        message(NOTICE "[cpprog] Prefer modules when writing C++ code.")
    endif()

    list(APPEND arg_DEPENDENCIES cpprog)

    add_executable("${arg_TARGET}")
    target_sources("${arg_TARGET}" PRIVATE FILE_SET CXX_MODULES FILES ${arg_CXX_MODULES} PRIVATE ${arg_CXX_SOURCES})
    target_link_libraries("${arg_TARGET}" PRIVATE ${arg_DEPENDENCIES})
    _cpprog_set_compiler_options("${arg_TARGET}")
    _cpprog_enable_sanitizers("${arg_TARGET}")
    _cpprog_enable_clangtidy("${arg_TARGET}" "${arg_DEPENDENCIES}")
endfunction()

function(cpprog_add_library)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs CXX_MODULES CXX_SOURCES INCLUDE_DIRECTORIES DEPENDENCIES)
    cmake_parse_arguments(PARSE_ARGV 0 arg "${OPTIONS}" "${oneValueArgs}" "${multiValueArgs}")

    if(NOT arg_TARGET)
        message(FATAL_ERROR "[cpprog] Missing argument TARGET. Library name is required!")
    endif()
    if ((NOT arg_CXX_MODULES) OR arg_CXX_SOURCES)
        message(NOTICE "[cpprog] Prefer modules when writing C++ code.")
    endif()

    if(NOT "${arg_TARGET}" STREQUAL "cpprog")
        list(APPEND arg_DEPENDENCIES cpprog)
    endif()

    add_library("${arg_TARGET}")
    target_sources("${arg_TARGET}" PUBLIC FILE_SET CXX_MODULES FILES ${arg_CXX_MODULES} PRIVATE ${arg_CXX_SOURCES})
    target_include_directories("${arg_TARGET}" INTERFACE ${arg_INCLUDE_DIRECTORIES})
    target_link_libraries("${arg_TARGET}" PRIVATE ${arg_DEPENDENCIES})
    _cpprog_set_compiler_options("${arg_TARGET}")
    _cpprog_enable_sanitizers("${arg_TARGET}")
    _cpprog_enable_clangtidy("${arg_TARGET}" "${arg_DEPENDENCIES}")
endfunction()

function(cpprog_add_test)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs CXX_MODULES CXX_SOURCES DEPENDENCIES)
    cmake_parse_arguments(PARSE_ARGV 0 arg "${OPTIONS}" "${oneValueArgs}" "${multiValueArgs}")

    if(NOT arg_TARGET)
        message(FATAL_ERROR "[cpprog] Missing argument TARGET. Test name is required!")
    endif()
    if(NOT arg_CXX_SOURCES)
        message(FATAL_ERROR "[cpprog] Missing argument CXX_SOURCES. At least one source file is required!")
    endif()
    if(arg_CXX_MODULES)
        message(NOTICE "[cpprog] Prefer moving module files with reusable code to a separate library.")
    endif()

    list(APPEND arg_DEPENDENCIES cpprog)

    add_executable("${arg_TARGET}")
    target_sources("${arg_TARGET}" PRIVATE FILE_SET CXX_MODULES FILES ${arg_CXX_MODULES} PRIVATE ${arg_CXX_SOURCES})
    target_link_libraries("${arg_TARGET}" PRIVATE Catch2::Catch2WithMain ${arg_DEPENDENCIES})
    _cpprog_set_compiler_options("${arg_TARGET}")
    _cpprog_enable_sanitizers("${arg_TARGET}")
    _cpprog_enable_clangtidy("${arg_TARGET}" "${arg_DEPENDENCIES}")
    catch_discover_tests("${arg_TARGET}" TEST_PREFIX "${arg_TARGET}." REPORTER compact)
endfunction()

function(_cpprog_set_compiler_options target_name)
    set(cpprog_COMMON_WARNINGS
        "-Wall;-Wextra;-Wpedantic;-Wshadow;-Wconversion;-Wsign-conversion;-Wdouble-promotion;"
        "-Wcast-align;-Wunused;-Wnull-dereference;-Wimplicit-fallthrough;-Wformat=2;-Werror")

    set(cpprog_C_WARNINGS "${cpprog_COMMON_WARNINGS}")
    set(cpprog_CXX_WARNINGS "${cpprog_COMMON_WARNINGS};"
        "-Wnon-virtual-dtor;-Wold-style-cast;-Woverloaded-virtual;-Wextra-semi")

    target_compile_options("${target_name}" PRIVATE
        "-ffile-prefix-map=${CMAKE_SOURCE_DIR}=/project_root"
        "$<$<COMPILE_LANGUAGE:C>:${cpprog_C_WARNINGS}>"
        "$<$<COMPILE_LANGUAGE:CXX>:${cpprog_CXX_WARNINGS}>"
    )
endfunction()

function(_cpprog_enable_sanitizers target_name)
    set(cpprog_SANITIZERS "address,undefined")

    target_compile_options("${target_name}" PRIVATE
        "$<$<CONFIG:Debug>:-fsanitize=${cpprog_SANITIZERS};-fno-omit-frame-pointer>"
    )
    target_link_options("${target_name}" PRIVATE
        "$<$<CONFIG:Debug>:-fsanitize=${cpprog_SANITIZERS}>"
    )
endfunction()

function(_cpprog_enable_clangtidy target_name dependencies)
    get_target_property(cpprog_CXX_STANDARD "${target_name}" CXX_STANDARD)

    set(cpprog_C_CLANG_TIDY "${CLANG_TIDY}")
    set(cpprog_CXX_CLANG_TIDY
        "${CLANG_TIDY}"
        "--extra-arg=-fprebuilt-module-path=${CMAKE_BINARY_DIR}/CMakeFiles/__cmake_cxx${cpprog_CXX_STANDARD}.dir"
        "--extra-arg=-fprebuilt-module-path=${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${target_name}.dir"
    )

    foreach(cpprog_DEP IN LISTS dependencies)
        get_target_property(cpprog_DEP_DIR "${cpprog_DEP}" BINARY_DIR)
        list(APPEND cpprog_CXX_CLANG_TIDY "--extra-arg=-fprebuilt-module-path=${cpprog_DEP_DIR}/CMakeFiles/${cpprog_DEP}.dir")
    endforeach()

    set_target_properties("${target_name}" PROPERTIES C_CLANG_TIDY "${cpprog_C_CLANG_TIDY}")
    set_target_properties("${target_name}" PROPERTIES CXX_CLANG_TIDY "${cpprog_CXX_CLANG_TIDY}")
endfunction()
