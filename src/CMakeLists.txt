
list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/file2passwd.cpp
)

list(APPEND HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/main.hpp
    ${CMAKE_CURRENT_LIST_DIR}/file2passwd.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto gsl)
