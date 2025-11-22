cmake_minimum_required(VERSION 4.0)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)

find_package(OpenGL REQUIRED)

include_directories(include)

add_executable(LearnOpenGL
        src/main.cpp
        src/glad.c
        src/window.cpp
)

target_link_libraries(LearnOpenGL
        glfw
        OpenGL::GL
        "-framework Cocoa"
        "-framework IOKit"
)

if(APPLE)
    target_link_libraries(LearnOpenGL "-framework CoreVideo")
endif()