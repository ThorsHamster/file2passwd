cmake_minimum_required(VERSION 3.13)

if(${CMAKE_VERSION} VERSION_LESS 3.13)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(file2passwd VERSION 1.0
                    DESCRIPTION "Converts files to passwords."
                    LANGUAGES CXX)


list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(src)

option(CLANG_TIDY_TESTS "Test with clang-tidy" ON)
if(CLANG_TIDY_TESTS)
    include(clang_tidy)
endif()
