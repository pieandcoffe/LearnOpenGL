cmake_minimum_required(VERSION 3.20)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 20)

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
# Source files
# -------------------------------------------------------

set(SOURCES
        src/main.cpp
        src/glad.c

        # Platform
        src/platform/WindowHandle.cpp
        src/platform/InputHandle.cpp

        # Shader
        src/shader/program.cpp
        src/shader/stage.cpp
)

set(HEADERS
        # Core
        include/core/Config.h

        # Platform
        include/platform/WindowHandle.h
        include/platform/InputHandle.h

        # Shader
        include/shader/program.h
        include/shader/stage.h

        # Types
        include/types/Dimensions.h
        include/platform/GlfwUserData.h
)

# -------------------------------------------------------
# Target
# -------------------------------------------------------

add_executable(LearnOpenGL ${SOURCES} ${HEADERS})

# -------------------------------------------------------
# Include directories
# -------------------------------------------------------

target_include_directories(LearnOpenGL PRIVATE
        include
        ${PLATFORM_INCLUDES}
)

# -------------------------------------------------------
# Link libraries
# -------------------------------------------------------

target_link_libraries(LearnOpenGL PRIVATE
        ${PLATFORM_LIBS}
)

# -------------------------------------------------------
# Copy shaders directory after build
# -------------------------------------------------------

add_custom_command(
        TARGET LearnOpenGL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        ${CMAKE_BINARY_DIR}/shaders
        COMMENT "Copying shaders to build directory"
)