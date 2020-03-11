
include(AddGoogleTest)
include(BundleAllTests)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_include_directories(${TESTNAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src)
    target_link_libraries(${TESTNAME} f2p_lib gsl gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME} --gtest_output=xml:${TESTNAME}.xml)
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(file2passwd_tests file2passwd_tests.cpp)
package_add_test(utility_tests utilities_tests.cpp)
package_add_test(compatibility_layer_tests compatibility_layer_tests.cpp)

SETUP_ALLTESTS_TARGET(
    NAME all_tests                 
    EXECUTABLE GTEST_COLOR=1 ctest --verbose -j ${n_cores}
    DEPENDENCIES
        file2passwd_tests
        utility_tests
        compatibility_layer_tests
)

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

