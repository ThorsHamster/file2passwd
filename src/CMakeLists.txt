
list(APPEND f2p_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/file2passwd.cpp
    ${CMAKE_CURRENT_LIST_DIR}/compatibility_layer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/utilities.cpp
)

list(APPEND f2p_HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/file2passwd.hpp
    ${CMAKE_CURRENT_LIST_DIR}/compatibility_layer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/utilities.hpp
)

add_library(f2p_lib ${f2p_SOURCES} ${f2p_HEADERS})
target_link_libraries(f2p_lib PRIVATE OpenSSL::Crypto gsl)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC")

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE f2p_lib gsl)
