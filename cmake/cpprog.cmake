include_guard()

macro(cpprog_init)
    _cpprog_generate_compile_commands()
    _cpprog_enable_modules()
    _cpprog_set_cxx_standard()
    _cpprog_enable_lto()
    _cpprog_find_clang_tidy()
    _cpprog_generate_debuginit()
endmacro()

macro(_cpprog_generate_compile_commands)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    file(RELATIVE_PATH cpprog_RELATIVE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build ${CMAKE_CURRENT_BINARY_DIR})

    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink
                ${cpprog_RELATIVE_BINARY_DIR}/compile_commands.json
                compile_commands.json
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/build
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

macro(_cpprog_enable_modules)
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")
    set(CMAKE_CXX_MODULE_STD ON)
endmacro()

macro(_cpprog_set_cxx_standard)
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

macro(_cpprog_generate_debuginit)
    configure_file(${CMAKE_SOURCE_DIR}/lldbinit.in ${CMAKE_SOURCE_DIR}/.lldbinit)
endmacro()

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
        message(WARNING "[cpprog] There should only be one source file with main function. Other sources should be modules.")
    endif()

    list(APPEND arg_DEPENDENCIES cpprog)

    add_executable(${arg_TARGET})
    target_sources(${arg_TARGET} PRIVATE FILE_SET CXX_MODULES FILES ${arg_CXX_MODULES} PRIVATE ${arg_CXX_SOURCES})
    target_link_libraries(${arg_TARGET} PRIVATE ${arg_DEPENDENCIES})
    _cpprog_set_compiler_options(TARGET ${arg_TARGET})
    _cpprog_enable_sanitizers(TARGET ${arg_TARGET})
    _cpprog_enable_clangtidy(TARGET ${arg_TARGET} DEPENDENCIES ${arg_DEPENDENCIES})
endfunction()

function(cpprog_add_library)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs CXX_MODULES DEPENDENCIES)
    cmake_parse_arguments(PARSE_ARGV 0 arg "${OPTIONS}" "${oneValueArgs}" "${multiValueArgs}")

    if(NOT arg_TARGET)
        message(FATAL_ERROR "[cpprog] Missing argument TARGET. Library name is required!")
    endif()
    if (NOT arg_CXX_MODULES)
        message(FATAL_ERROR "[cpprog] Missing argument CXX_MODULES. At least one module is required!")
    endif()

    if(NOT "${arg_TARGET}" STREQUAL "cpprog")
        list(APPEND arg_DEPENDENCIES cpprog)
    endif()

    add_library(${arg_TARGET})
    target_sources(${arg_TARGET} PUBLIC FILE_SET CXX_MODULES FILES ${arg_CXX_MODULES})
    target_link_libraries(${arg_TARGET} PRIVATE ${arg_DEPENDENCIES})
    _cpprog_set_compiler_options(TARGET ${arg_TARGET})
    _cpprog_enable_sanitizers(TARGET ${arg_TARGET})
    _cpprog_enable_clangtidy(TARGET ${arg_TARGET} DEPENDENCIES ${arg_DEPENDENCIES})
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
        message(WARNING "[cpprog] Prefer moving module files with reusable code to a separate library.")
    endif()

    list(APPEND arg_DEPENDENCIES cpprog)

    add_executable(${arg_TARGET})
    target_sources(${arg_TARGET} PRIVATE FILE_SET CXX_MODULES FILES ${arg_CXX_MODULES} PRIVATE ${arg_CXX_SOURCES})
    target_link_libraries(${arg_TARGET} PRIVATE Catch2::Catch2WithMain ${arg_DEPENDENCIES})
    _cpprog_set_compiler_options(TARGET ${arg_TARGET})
    _cpprog_enable_sanitizers(TARGET ${arg_TARGET})
    _cpprog_enable_clangtidy(TARGET ${arg_TARGET} DEPENDENCIES ${arg_DEPENDENCIES})
    catch_discover_tests(${arg_TARGET} TEST_PREFIX "${arg_TARGET}." REPORTER compact)
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

function(_cpprog_enable_sanitizers)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs)
    cmake_parse_arguments(PARSE_ARGV 0 arg "${OPTIONS}" "${oneValueArgs}" "${multiValueArgs}")

    target_compile_options(${arg_TARGET} PRIVATE
        "$<$<CONFIG:Debug>:-fsanitize=address,undefined;-fno-omit-frame-pointer>"
    )
    target_link_options(${arg_TARGET} PRIVATE
        "$<$<CONFIG:Debug>:-fsanitize=address,undefined>"
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
