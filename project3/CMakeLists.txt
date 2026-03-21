cmake_minimum_required(VERSION 3.10)
project(P3)

#require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

# some definitions
set(SOURCE_STACK Stack.hpp Stack.tpp)
set(SOURCE_XMLPARSER XMLParser.hpp XMLParser.cpp ${SOURCE_STACK})
set(SOURCE_XMLPARSER_TEST test_XMLParser.cpp ${SOURCE_XMLPARSER})

# create unittests
add_executable(test-XMLParser catch.hpp ${SOURCE_XMLPARSER_TEST})

enable_testing()

# unit tests
add_test(test-XMLParser test-XMLParser)

# a rule to create the submission zip file
add_custom_target(submission COMMAND
    ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/p3_xml_parser.zip" --format=zip
    ${SOURCE_XMLPARSER_TEST}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
	     
