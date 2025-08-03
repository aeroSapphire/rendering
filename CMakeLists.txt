cmake_minimum_required(VERSION 3.14)
project(RenderCircle VERSION 0.1.0 LANGUAGES CXX)

# Use modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optional: More warnings and debug info
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(include)

# Create executable
# add_executable(${PROJECT_NAME} ${SOURCES})
add_executable(render_circle
    src/circle.cpp
    main/circle_main.cpp)

add_executable(render_checker_board
    src/checker_board.cpp
    main/checker_board_main.cpp)

add_executable(render_radial_checker_board
    src/radial_checker_board.cpp
    main/radial_checker_board_main.cpp)
