
list(APPEND SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

list(APPEND HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/main.hpp
)

add_executable(file2passwd ${SOURCES} ${HEADERS})
