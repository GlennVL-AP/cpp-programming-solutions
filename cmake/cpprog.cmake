include_guard()

macro(cpprog_init)
    _cpprog_generate_compile_commands()
    _cpprog_enable_cxx_modules()
    _cpprog_set_language_standards()
    _cpprog_enable_lto()
    _cpprog_find_clang_tidy()
    _cpprog_generate_debuginit()
endmacro()

macro(cpprog_configure_project)
    _cpprog_clion_clangd_workaround()
    _cpprog_enable_testing()
endmacro()

macro(_cpprog_generate_compile_commands)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

    cmake_path(RELATIVE_PATH CMAKE_CURRENT_BINARY_DIR BASE_DIRECTORY "${CMAKE_SOURCE_DIR}/build" OUTPUT_VARIABLE cpprog_RELATIVE_BINARY_DIR)

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

function(_cpprog_clion_clangd_workaround)
    if($ENV{CLION_IDE})
        message(STATUS "[cpprog] Detected clion, applying workaround for module std.")
        set(cpprog_LIBCXX_DIR "/usr/lib/llvm-20/share/libc++/v1")
        if(NOT EXISTS "${cpprog_LIBCXX_DIR}")
            message(FATAL_ERROR "[cpprog] libc++ not found at ${cpprog_LIBCXX_DIR}")
        endif()
        add_library(clion_workaround_std_target STATIC EXCLUDE_FROM_ALL)
        target_sources(clion_workaround_std_target
            PRIVATE FILE_SET CXX_MODULES
            BASE_DIRS "${cpprog_LIBCXX_DIR}"
            FILES "${cpprog_LIBCXX_DIR}/std.cppm" "${cpprog_LIBCXX_DIR}/std.compat.cppm"
        )
    endif()
endfunction()

macro(_cpprog_enable_testing)
    include(CTest)
    enable_testing()
    find_package(Catch2 CONFIG REQUIRED)
    include(Catch)
endmacro()

function(cpprog_generate_version_info)
    set(options)
    set(oneValueArgs TARGET INPUT_FILE OUTPUT_FILE)
    set(multiValueArgs)
    cmake_parse_arguments(PARSE_ARGV 0 arg "${OPTIONS}" "${oneValueArgs}" "${multiValueArgs}")

    if(NOT TARGET "${arg_TARGET}")
        message(FATAL_ERROR "[cpprog] Target ${arg_TARGET} does not exist.")
    endif()

    cmake_path(ABSOLUTE_PATH arg_INPUT_FILE BASE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" NORMALIZE OUTPUT_VARIABLE cpprog_INPUT_FILE)
    cmake_path(ABSOLUTE_PATH arg_OUTPUT_FILE BASE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" NORMALIZE OUTPUT_VARIABLE cpprog_OUTPUT_FILE)

    set(cpprog_VERSION_TARGET "${cpprog_OUTPUT_FILE}")
    string(REPLACE "/" "_" cpprog_VERSION_TARGET "${cpprog_VERSION_TARGET}")

    add_custom_target(
        "${cpprog_VERSION_TARGET}" ALL
        COMMAND "${CMAKE_COMMAND}"
            -DPROJECT_ROOT="${CMAKE_SOURCE_DIR}"
            -DINPUT_FILE="${cpprog_INPUT_FILE}"
            -DOUTPUT_FILE="${cpprog_OUTPUT_FILE}"
            -DVERSION_MAJOR="${${CMAKE_PROJECT_NAME}_VERSION_MAJOR}"
            -DVERSION_MINOR="${${CMAKE_PROJECT_NAME}_VERSION_MINOR}"
            -DVERSION_PATCH="${${CMAKE_PROJECT_NAME}_VERSION_PATCH}"
            -P "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/generate_version_info.cmake"
        BYPRODUCTS "${cpprog_OUTPUT_FILE}"
        COMMENT "[cpprog] Generating version info."
    )

    add_dependencies("${arg_TARGET}" "${cpprog_VERSION_TARGET}")
    target_sources("${arg_TARGET}" PUBLIC FILE_SET CXX_MODULES BASE_DIRS "${CMAKE_CURRENT_BINARY_DIR}" FILES "${cpprog_OUTPUT_FILE}")
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

    add_executable("${arg_TARGET}")
    _cpprog_configure_target("${arg_TARGET}" "${arg_CXX_MODULES}" "${arg_CXX_SOURCES}" "" "${arg_DEPENDENCIES}")
endfunction()

function(cpprog_add_library)
    set(options)
    set(oneValueArgs TARGET)
    set(multiValueArgs CXX_MODULES CXX_SOURCES CXX_HEADERS DEPENDENCIES)
    cmake_parse_arguments(PARSE_ARGV 0 arg "${OPTIONS}" "${oneValueArgs}" "${multiValueArgs}")

    if(NOT arg_TARGET)
        message(FATAL_ERROR "[cpprog] Missing argument TARGET. Library name is required!")
    endif()
    if ((NOT arg_CXX_MODULES) OR arg_CXX_SOURCES)
        message(NOTICE "[cpprog] Prefer modules when writing C++ code.")
    endif()

    add_library("${arg_TARGET}")
    add_library("${CMAKE_PROJECT_NAME}::${arg_TARGET}" ALIAS "${arg_TARGET}")
    _cpprog_configure_target("${arg_TARGET}" "${arg_CXX_MODULES}" "${arg_CXX_SOURCES}" "${arg_CXX_HEADERS}" "${arg_DEPENDENCIES}")
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

    list(APPEND arg_DEPENDENCIES Catch2::Catch2WithMain)

    add_executable("${arg_TARGET}")
    _cpprog_configure_target("${arg_TARGET}" "${arg_CXX_MODULES}" "${arg_CXX_SOURCES}" "" "${arg_DEPENDENCIES}")
    catch_discover_tests("${arg_TARGET}" TEST_PREFIX "${arg_TARGET}." REPORTER compact)
endfunction()

function(_cpprog_configure_target target_name modules sources headers dependencies)
    if(NOT "${target_name}" STREQUAL "cpprog")
        list(APPEND dependencies cpprog)
    endif()

    target_sources("${target_name}"
        PUBLIC FILE_SET HEADERS FILES ${headers}
        PUBLIC FILE_SET CXX_MODULES FILES ${modules}
        PRIVATE ${sources}
    )

    target_link_libraries("${target_name}" PRIVATE ${dependencies})

    _cpprog_set_compiler_options("${target_name}")
    _cpprog_enable_sanitizers("${target_name}")
    _cpprog_enable_clangtidy("${target_name}" "${dependencies}")
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
        if(TARGET "${cpprog_DEP}")
            get_target_property(cpprog_DEP_DIR "${cpprog_DEP}" BINARY_DIR)
            list(APPEND cpprog_CXX_CLANG_TIDY "--extra-arg=-fprebuilt-module-path=${cpprog_DEP_DIR}/CMakeFiles/${cpprog_DEP}.dir")
        endif()
    endforeach()

    set_target_properties("${target_name}" PROPERTIES C_CLANG_TIDY "${cpprog_C_CLANG_TIDY}")
    set_target_properties("${target_name}" PROPERTIES CXX_CLANG_TIDY "${cpprog_CXX_CLANG_TIDY}")
endfunction()
