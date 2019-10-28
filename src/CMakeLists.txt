
list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/file2passwd.cpp
    ${CMAKE_CURRENT_LIST_DIR}/compatibility_layer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/utilities.cpp
)

list(APPEND HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/main.hpp
    ${CMAKE_CURRENT_LIST_DIR}/file2passwd.hpp
    ${CMAKE_CURRENT_LIST_DIR}/compatibility_layer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/utilities.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto gsl)
