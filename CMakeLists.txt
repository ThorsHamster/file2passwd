cmake_minimum_required(VERSION 3.12)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(file2passwd VERSION 1.0
                    DESCRIPTION "Converts files to passwords."
                    LANGUAGES CXX C
)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

option(GOOGLE_TESTS "Build the tests" ON)
option(BUILD_PYTHON "Build Python Library" OFF)
option(CLANG_TIDY_TESTS "Test with clang-tidy" OFF)
option(BUILD_DOC "Build documentation" OFF)
option(CODE_COVERAGE "Enable coverage reporting" OFF)

message(STATUS "Google Tests: ${GOOGLE_TESTS}")
message(STATUS "Build Python: ${BUILD_PYTHON}")
message(STATUS "Test with clang-tidy: ${CLANG_TIDY_TESTS}")
message(STATUS "Generate documentation: ${BUILD_DOC}")
message(STATUS "Coverage reporting: ${CODE_COVERAGE}")


if(NOT GOOGLE_TESTS)

    find_package(OpenSSL REQUIRED)

    # Guideline support library, gsl
    include(gsl)

    add_subdirectory(src)

    if(CLANG_TIDY_TESTS)
        include(clang_tidy)
    endif()

    if(BUILD_PYTHON)
        add_subdirectory(python)
    endif()

    if(BUILD_DOC)
        include(doxygen)
    endif()

else()
    if(CODE_COVERAGE)
      include(CodeCoverage)
      APPEND_COVERAGE_COMPILER_FLAGS()
    endif(CODE_COVERAGE)

    enable_testing()
    add_subdirectory(tests)
endif()