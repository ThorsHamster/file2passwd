
include(AddGoogleTest)
include(AddTestPackage)

add_testpackage(TEST_NAME 
                    utility_tests 
                SOURCES 
                    utilities_tests.cpp
                    ${CMAKE_SOURCE_DIR}/src/utilities.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/openssl
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/gsl
)

add_testpackage(TEST_NAME 
                    file_reader_tests 
                SOURCES 
                    file_reader_tests.cpp
                    ${CMAKE_SOURCE_DIR}/src/file_reader.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/openssl
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/gsl
)

add_testpackage(TEST_NAME 
                    openssl_tests 
                SOURCES 
                    openssl_tests.cpp
                    ${CMAKE_SOURCE_DIR}/src/openssl.cpp
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/openssl/md5.c
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/openssl
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/gsl
)

add_testpackage(TEST_NAME 
                    exception_tests 
                SOURCES 
                    exception_tests.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/openssl
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/gsl
)

add_testpackage(TEST_NAME 
                    file2passwd_tests 
                SOURCES 
                    file2passwd_tests.cpp
                    ${CMAKE_SOURCE_DIR}/src/file2passwd.cpp
                TEST_INCLUDE_DIRECTORIES 
                    ${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/openssl
                    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/gsl
)

# necessary for unit tests, to have a specific file for testing
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

if(CODE_COVERAGE)
  SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage                 
        EXECUTABLE ctest
            )
endif(CODE_COVERAGE)
