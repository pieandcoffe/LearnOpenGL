cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)

# -------------------------------------------------------
# Platform-specific configuration
# -------------------------------------------------------

if(APPLE)
    find_package(glfw3 REQUIRED)
    find_package(glm REQUIRED)
    find_package(OpenGL REQUIRED)

    set(PLATFORM_LIBS
            glfw
            glm::glm
            OpenGL::GL
            "-framework Cocoa"
            "-framework IOKit"
            "-framework CoreVideo"
    )
    set(PLATFORM_INCLUDES "")

elseif(WIN32)
    set(GLFW_DIR ${CMAKE_SOURCE_DIR}/libs/glfw)
    set(GLM_DIR  ${CMAKE_SOURCE_DIR}/libs/glm)

    set(PLATFORM_LIBS
            ${GLFW_DIR}/lib-mingw-w64/libglfw3.a
            opengl32
            gdi32
            user32
            shell32
    )
    set(PLATFORM_INCLUDES
            ${GLFW_DIR}/include
            ${GLM_DIR}
    )
endif()

# -------------------------------------------------------
# Includes
# -------------------------------------------------------

include_directories(
        include
        ${PLATFORM_INCLUDES}
)

# -------------------------------------------------------
# Source files
# -------------------------------------------------------

add_executable(LearnOpenGL
        src/main.cpp
        src/glad.c
        src/viewport/dimensions.cpp
        src/viewport/window.cpp
        src/shader/program.cpp
        src/shader/stage.cpp
)

# -------------------------------------------------------
# Link libraries
# -------------------------------------------------------

target_link_libraries(LearnOpenGL ${PLATFORM_LIBS})

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