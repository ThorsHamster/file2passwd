
list(APPEND my_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/main.h
)

add_executable(file2passwd ${my_SOURCES})
