cmake_minimum_required(VERSION 3.14)
project(RenderCircle VERSION 0.1.0 LANGUAGES CXX)
set(FETCHCONTENT_QUIET OFF CACHE BOOL "Show FetchContent progress")
include(FetchContent)

# Get a specific glm release (pin the tag you want)
FetchContent_Declare(glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG        1.0.1        # <- pick a release/tag or commit
)

# Optional: turn off glm's tests/examples if present
set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glm)

# Use modern C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optional: More warnings and debug info
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wpedantic)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(include ${GLM_INCLUDE_DIRS})


# Create executable
# add_executable(${PROJECT_NAME} ${SOURCES})
add_executable(render_circle
    circle.cpp
    circle_render_main.cpp)

add_executable(render_checker_board
    checker_board.cpp
    checker_board_main.cpp)

add_executable(render_radial_checker_board
    radial_checker_board.cpp
    radial_checker_board_main.cpp)

add_executable(sphere_renderer
    camera_matrix.cpp
    sphere_render_main.cpp)

add_executable(test_render
    image_render_main.cpp
    camera_matrix.cpp)

add_executable(cone_render
    cone_render_main.cpp
    camera_matrix.cpp)

target_link_libraries(render_circle PRIVATE glm::glm)
target_link_libraries(render_checker_board PRIVATE glm::glm)
target_link_libraries(render_radial_checker_board PRIVATE glm::glm)
target_link_libraries(sphere_renderer PRIVATE glm::glm)
target_link_libraries(test_render PRIVATE glm::glm)
target_link_libraries(cone_render PRIVATE glm::glm)
