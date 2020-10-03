
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
    )
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME} --gtest_output=xml:${TESTNAME}.xml)
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(utility_tests
    utilities_tests.cpp
    ${CMAKE_SOURCE_DIR}/src/utilities.cpp
)

#package_add_test(compatibility_layer_tests
#    compatibility_layer_tests.cpp
#    ${CMAKE_SOURCE_DIR}/src/compatibility_layer.cpp
#)

#package_add_test(file2passwd_tests
#    file2passwd_tests.cpp
#    ${CMAKE_SOURCE_DIR}/src/file2passwd.cpp
#)

#package_add_test(system_tests
#    system_tests.cpp
#    ${CMAKE_SOURCE_DIR}/src/utilities.cpp
#    ${CMAKE_SOURCE_DIR}/src/compatibility_layer.cpp
#    ${CMAKE_SOURCE_DIR}/src/file2passwd.cpp
#)

SETUP_ALLTESTS_TARGET(
    NAME all_tests                 
    EXECUTABLE GTEST_COLOR=1 GTEST_REPEAT=3 GTEST_SHUFFLE=1 ctest --verbose -j ${n_cores}
    DEPENDENCIES
        utility_tests
        #file2passwd_tests
        #compatibility_layer_tests
        #system_tests
)

# necessary for unit tests, to have a specific file for testing
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE
     DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../tests/system_test.py
     DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

if(CODE_COVERAGE)
  SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME coverage                 
        EXECUTABLE ctest -j ${n_cores} # Executable in PROJECT_BINARY_DIR
        DEPENDENCIES
            all_tests
            )
endif(CODE_COVERAGE)

