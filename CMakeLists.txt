cmake_minimum_required(VERSION 3.20.0)
project(snake_game C CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

include_directories(".")
add_subdirectory(lib)

add_executable(${PROJECT_NAME}
    main.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY SUFFIX ".exe")

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        ${CURSES_LIBRARIES}
    PRIVATE
        lib
)