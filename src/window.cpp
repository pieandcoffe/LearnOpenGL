//
// Created by Kyrylo Pylinskyi on 22/11/2025.
//

#include <glad/glad.h>
#include "window.h"
#include <iostream>

Window::Window(const int width, const int height, const char *title)
    : m_window(nullptr)
    , m_width(width)
    , m_height(height)
    , m_title(title)
{
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

bool Window::init() {
    if (!initGLFW()) {
        return false;
    }

    if (!initGLAD()) {
        return false;
    }

    setupCallbacks();

    std::cout << "Window initialized successfully" << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    return true;
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::processInput() const {
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }
}

void Window::clear(const float r, const float g, const float b, const float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swapBuffers() const {
    glfwSwapBuffers(m_window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

GLFWwindow * Window::getGLFWWindow() const {
    return m_window;
}

int Window::getWidth() const {
    return m_width;
}

int Window::getHeight() const {
    return m_height;
}

bool Window::initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // Set OpenGL version and profile
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Mac OS
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width, m_height, "LearnOpenGL", nullptr, nullptr);
    if (m_window == nullptr) {
        std::cout << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);
    return true;
}

bool Window::initGLAD() const {
    if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cout << "Failed to initialize GLAD." << std::endl;
        return false;
    }

    glViewport(0, 0, m_width, m_height);
    return true;
}

void Window::setupCallbacks() const {
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
}

void Window::framebuffer_size_callback(GLFWwindow *window, const int width, const int height) {
    glViewport(0, 0, width, height);
}
