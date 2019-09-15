
list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/file2passwd.cpp
)

list(APPEND HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/main.hpp
    ${CMAKE_CURRENT_LIST_DIR}/file2passwd.hpp
)

add_executable(file2passwd ${SOURCES} ${HEADERS})
