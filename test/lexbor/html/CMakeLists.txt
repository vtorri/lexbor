cmake_minimum_required(VERSION 2.8)

################
## Search and Includes
#########################
include_directories(".")

################
## Sources
#########################
file(GLOB_RECURSE TEST_LEXBOR_HTML_SOURCES "*.c")

if(LEXBOR_BUILD_TESTS_CPP)
    file(GLOB_RECURSE TEST_LEXBOR_HTML_SOURCES_CPP "*.cpp")
endif()

################
## ARGS for tests
#########################
set(tokenizer_tokens_arg "${CMAKE_SOURCE_DIR}/test/files/lexbor/html/tokenizer")
set(tree_builder_arg "${CMAKE_SOURCE_DIR}/test/files/lexbor/html/html5_test")

################
## Create tests
#########################
IF(LEXBOR_BUILD_SHARED)
    EXECUTABLE_LIST("lexbor_html_" "${TEST_LEXBOR_HTML_SOURCES}" ${TEST_UNIT_LIB_NAME} ${LEXBOR_LIB_NAME})
    APPEND_TESTS("lexbor_html_" "${TEST_LEXBOR_HTML_SOURCES}")

    IF(LEXBOR_BUILD_TESTS_CPP)
        EXECUTABLE_LIST("lexbor_html_" "${TEST_LEXBOR_HTML_SOURCES_CPP}" ${TEST_UNIT_LIB_NAME} ${LEXBOR_LIB_NAME})
        APPEND_TESTS("lexbor_html_" "${TEST_LEXBOR_HTML_SOURCES_CPP}")
    ENDIF()
ENDIF()
