cmake_minimum_required(VERSION 3.12)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(file2passwd VERSION 1.0
                    DESCRIPTION "Converts files to passwords."
                    LANGUAGES CXX
)

find_package(OpenSSL REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

option(GOOGLE_TESTS "Build the tests" OFF)
option(BUILD_PYTHON "Build Python Library" OFF)
option(CLANG_TIDY_TESTS "Test with clang-tidy" OFF)
option(BUILD_DOC "Build documentation" ON)

message(STATUS "Google Tests: ${GOOGLE_TESTS}")
message(STATUS "Build Python: ${BUILD_PYTHON}")
message(STATUS "Test with clang-tidy: ${CLANG_TIDY_TESTS}")
message(STATUS "Generate documentation: ${BUILD_DOC}")

# Guideline support library, gsl
include(gsl)

add_subdirectory(src)

# google tests
if(GOOGLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# clang tidy
if(CLANG_TIDY_TESTS)
    include(clang_tidy)
endif()

# build python binding
if(BUILD_PYTHON)
    add_subdirectory(python)
endif()

# generate documentation
if(BUILD_DOC)
    include(doxygen)
endif()
