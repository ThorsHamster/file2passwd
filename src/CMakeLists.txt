
list(APPEND f2p_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/file2passwd_interface.cpp
    ${CMAKE_CURRENT_LIST_DIR}/file2passwd.cpp
    ${CMAKE_CURRENT_LIST_DIR}/compatibility_layer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/utilities.cpp
    ${CMAKE_CURRENT_LIST_DIR}/file_reader.cpp
    ${CMAKE_CURRENT_LIST_DIR}/openssl.cpp
)

list(APPEND f2p_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/file2passwd_interface.hpp
    ${CMAKE_CURRENT_LIST_DIR}/file2passwd.hpp
    ${CMAKE_CURRENT_LIST_DIR}/compatibility_layer_interface.hpp
    ${CMAKE_CURRENT_LIST_DIR}/compatibility_layer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/utilities_interface.hpp
    ${CMAKE_CURRENT_LIST_DIR}/utilities.hpp
    ${CMAKE_CURRENT_LIST_DIR}/file_reader_interface.hpp
    ${CMAKE_CURRENT_LIST_DIR}/file_reader.hpp
    ${CMAKE_CURRENT_LIST_DIR}/openssl.hpp
    ${CMAKE_CURRENT_LIST_DIR}/openssl_interface.hpp
)

add_library(f2p_lib ${f2p_SOURCES} ${f2p_HEADERS})
target_link_libraries(f2p_lib PRIVATE OpenSSL::Crypto gsl)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC" CACHE INTERNAL "C++ flags")  # needed for linking python .so

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE f2p_lib gsl)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../LICENSE
     DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../tests/system_test.py
     DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)