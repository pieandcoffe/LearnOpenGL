cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)

# Packages
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)

# Includes
include_directories(include)

# Source files
add_executable(LearnOpenGL
        src/main.cpp
        src/glad.c
        src/viewport/dimensions.cpp
        src/viewport/window.cpp
        src/shader/program.cpp
        src/shader/stage.cpp
)

# Link libraries
target_link_libraries(LearnOpenGL
        glfw
        glm::glm
        OpenGL::GL
)

# macOS frameworks
if(APPLE)
    target_link_libraries(LearnOpenGL
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
    )
endif()


# -------------------------------------------------------
# Copy shaders directory after build
# -------------------------------------------------------

add_custom_command(
        TARGET LearnOpenGL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory
        ${CMAKE_BINARY_DIR}/shaders
)

add_custom_command(
        TARGET LearnOpenGL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        ${CMAKE_BINARY_DIR}/shaders
)