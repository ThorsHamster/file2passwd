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

option(GOOGLE_TESTS "Build the tests" ON)
option(BUILD_PYTHON "Build Python Library" OFF)
option(CLANG_TIDY_TESTS "Test with clang-tidy" OFF)
option(BUILD_DOC "Build documentation" ON)
option(CODE_COVERAGE "Enable coverage reporting" OFF)

message(STATUS "Google Tests: ${GOOGLE_TESTS}")
message(STATUS "Build Python: ${BUILD_PYTHON}")
message(STATUS "Test with clang-tidy: ${CLANG_TIDY_TESTS}")
message(STATUS "Generate documentation: ${BUILD_DOC}")
message(STATUS "Coverage reporting: ${CODE_COVERAGE}")

# Guideline support library, gsl
include(gsl)

# Code Coverage Configuration
add_library(coverage_config INTERFACE)

if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  # Add required flags (GCC & LLVM/Clang)
  target_compile_options(coverage_config INTERFACE
    -O0        # no optimization
    -g         # generate debug info
    --coverage # sets all required flags
  )
  if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
    target_link_options(coverage_config INTERFACE --coverage)
  else()
    target_link_libraries(coverage_config INTERFACE --coverage)
  endif()
endif(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

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
