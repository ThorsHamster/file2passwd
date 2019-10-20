
include(AddGoogleTest)

list(APPEND SOURCES
    ${CMAKE_SOURCE_DIR}/src/file2passwd.cpp
    ${CMAKE_SOURCE_DIR}/src/compatibility_layer.cpp
)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN} ${SOURCES})
    target_include_directories(${TESTNAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src)
    target_link_libraries(${TESTNAME} OpenSSL::Crypto gsl gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(file2passwd_integrationtest file2passwd_integrationtest.cpp)