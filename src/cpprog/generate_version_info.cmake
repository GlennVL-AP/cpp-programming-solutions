if(NOT PROJECT_ROOT)
    message(FATAL_ERROR "[cpprog] Missing argument PROJECT_ROOT.")
endif()

if(NOT INPUT_FILE)
    message(FATAL_ERROR "[cpprog] Missing argument INPUT_FILE.")
endif()

if(NOT OUTPUT_FILE)
    message(FATAL_ERROR "[cpprog] Missing argument OUTPUT_FILE.")
endif()

if(NOT VERSION_MAJOR)
    set(VERSION_MAJOR 0)
endif()
if(NOT VERSION_MINOR)
    set(VERSION_MINOR 0)
endif()
if(NOT VERSION_PATCH)
    set(VERSION_PATCH 0)
endif()

execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY "${PROJECT_ROOT}"
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE GIT_REV_PARSE_RESULT
    ERROR_QUIET
)

if(NOT GIT_REV_PARSE_RESULT EQUAL 0)
    message(STATUS "[cpprog] Not a git repository.")
    set(GIT_COMMIT_HASH "unknown")
endif()

message(STATUS "[cpprog] Generating ${OUTPUT_FILE}.")
message(STATUS "[cpprog] VERSION=${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}, GIT_COMMIT_HASH=${GIT_COMMIT_HASH}")

configure_file("${INPUT_FILE}" "${OUTPUT_FILE}" @ONLY)
