//
// Created by Kyrylo Pylinskyi on 22/11/2025.
//

#include "viewport/window.h"

#include <glad/glad.h>
#include <iostream>

#include "viewport/dimensions.h"

namespace Viewport
{
    Window::Window(const char* title, const int width, const int height)
        : m_window(nullptr)
        , m_dimensions(width, height) // FIXED: width first, then height
        , m_title(title)
    {
    }

    Window::~Window()
    {
        if (m_window)
        {
            glfwDestroyWindow(m_window);
        }
        glfwTerminate();
    }

    // Move constructor
    Window::Window(Window&& other) noexcept
        : m_window(other.m_window)
        , m_dimensions(std::move(other.m_dimensions))
        , m_title(std::move(other.m_title))
    {
        other.m_window = nullptr;
    }

    // Move assignment
    Window& Window::operator=(Window&& other) noexcept
    {
        if (this != &other)
        {
            // Clean up existing resources
            if (m_window)
            {
                glfwDestroyWindow(m_window);
            }

            // Transfer ownership
            m_window = other.m_window;
            m_dimensions = std::move(other.m_dimensions);
            m_title = std::move(other.m_title);

            // Update user pointer for callbacks
            if (m_window)
            {
                glfwSetWindowUserPointer(m_window, this);
            }

            // Nullify moved-from object
            other.m_window = nullptr;
        }
        return *this;
    }

    bool Window::init()
    {
        if (!initGLFW())
        {
            return false;
        }

        if (!initGLAD())
        {
            return false;
        }

        setupCallbacks();
        m_dimensions.updateFromWindow(m_window);

        std::cout << "Window initialized successfully" << std::endl;
        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "Window size: " << m_dimensions.getWindowWidth() << "x" << m_dimensions.getWindowHeight()
                  << std::endl;
        std::cout << "Framebuffer size: " << m_dimensions.getBufferWidth() << "x" << m_dimensions.getBufferHeight()
                  << std::endl;

        if (m_dimensions.isHiDPI())
        {
            std::cout << "HiDPI display detected (pixel scale: " << m_dimensions.getPixelScale() << "x)" << std::endl;
        }

        return true;
    }

    bool Window::shouldClose() const
    {
        return glfwWindowShouldClose(m_window);
    }

    void Window::processInput() const
    {
        if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(m_window, GLFW_TRUE);
        }
    }

    void Window::clear(const float r, const float g, const float b, const float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Window::swapBuffers() const
    {
        glfwSwapBuffers(m_window);
    }

    void Window::pollEvents()
    {
        glfwPollEvents();
    }

    // Getters
    GLFWwindow* Window::getGLFWWindow() const
    {
        return m_window;
    }

    const Dimensions& Window::getDimensions() const
    {
        return m_dimensions;
    }

    int Window::getWidth() const
    {
        return m_dimensions.getWindowWidth();
    }

    int Window::getHeight() const
    {
        return m_dimensions.getWindowHeight();
    }

    int Window::getFramebufferWidth() const
    {
        return m_dimensions.getBufferWidth();
    }

    int Window::getFramebufferHeight() const
    {
        return m_dimensions.getBufferHeight();
    }

    float Window::getAspectRatio() const
    {
        return m_dimensions.getAspectRatio();
    }

    // Private methods
    bool Window::initGLFW()
    {
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return false;
        }

        // Set OpenGL version and profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required for macOS

        m_window = glfwCreateWindow(m_dimensions.getWindowWidth(), m_dimensions.getWindowHeight(),
                                    m_title.c_str(), // FIXED: Use m_title instead of hardcoded string
                                    nullptr, nullptr);

        if (m_window == nullptr)
        {
            std::cerr << "Failed to create GLFW window." << std::endl;
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_window);
        return true;
    }

    bool Window::initGLAD() // FIXED: Removed const
    {
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            std::cerr << "Failed to initialize GLAD." << std::endl;
            return false;
        }

        // Update dimensions before applying viewport
        m_dimensions.updateFromWindow(m_window);

        // Apply viewport using framebuffer dimensions
        m_dimensions.applyViewport();

        return true;
    }

    void Window::setupCallbacks() // FIXED: Removed const
    {
        // Store 'this' pointer in GLFW window user pointer
        // This allows the callback to access the Window instance
        glfwSetWindowUserPointer(m_window, this);
        glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    }

    void Window::framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
    {
        // Get the Window instance from user pointer
        Window* windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window));

        if (windowInstance)
        {
            // Update dimensions
            windowInstance->m_dimensions.updateFromWindow(window);

            // Apply new viewport
            windowInstance->m_dimensions.applyViewport();

            std::cout << "Viewport resized to: " << width << "x" << height << std::endl;
        }
        else
        {
            // Fallback if user pointer not set (shouldn't happen)
            glViewport(0, 0, width, height);
        }
    }
} // namespace Viewport