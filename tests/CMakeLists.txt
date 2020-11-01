
include(AddGoogleTest)
include(BundleAllTests)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_include_directories(${TESTNAME} 
      PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR} 
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/tests/mock_libraries
        ${CMAKE_SOURCE_DIR}/tests/mock_libraries/openssl
        ${CMAKE_SOURCE_DIR}/tests/mock_libraries/gsl
    )
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME} --gtest_output=xml:${TESTNAME}.xml)
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(utility_tests
    utilities_tests.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities.cpp
)

package_add_test(file_reader_tests
    file_reader_tests.cpp
    ${CMAKE_SOURCE_DIR}/src/file_reader.cpp
)

package_add_test(openssl_tests
    openssl_tests.cpp
    ${CMAKE_SOURCE_DIR}/src/openssl.cpp
    ${CMAKE_SOURCE_DIR}/tests/mock_libraries/openssl/md5.c
)

package_add_test(exception_tests
    exception_tests.cpp
)

package_add_test(file2passwd_tests
    file2passwd_tests.cpp
    ${CMAKE_SOURCE_DIR}/src/file2passwd.cpp
)

SETUP_ALLTESTS_TARGET(
    NAME all_tests                 
    EXECUTABLE GTEST_COLOR=1 GTEST_REPEAT=3 GTEST_SHUFFLE=1 ctest --verbose -j ${n_cores}
    DEPENDENCIES
        file_reader_tests
        utility_tests
        file2passwd_tests
        exception_tests
        openssl_tests
)

# necessary for unit tests, to have a specific file for testing
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

if(CODE_COVERAGE)
  SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage                 
        EXECUTABLE ctest -j ${n_cores} # Executable in PROJECT_BINARY_DIR
        DEPENDENCIES
            all_tests
            )
endif(CODE_COVERAGE)

