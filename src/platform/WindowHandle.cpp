//
// Created by pieandcoffe on 15/03/2026.
//

#include "platform/WindowHandle.h"
#include "graphics.h"

#include <iostream>

namespace Platform
{
    WindowHandle::WindowHandle(const Core::AppConfig& config)
        : m_handle(nullptr)
        , m_dimensions(config.window)
        , m_config(config)
    {}

    WindowHandle::~WindowHandle()
    {
        if (m_handle)
        {
            glfwDestroyWindow(m_handle);
            m_handle = nullptr;
        }
        glfwTerminate();
    }

    WindowHandle::WindowHandle(WindowHandle&& other) noexcept
        : m_handle(other.m_handle)
        , m_dimensions(other.m_dimensions)
        , m_config(other.m_config)
        , onFramebufferResize(std::move(other.onFramebufferResize))
    {
        other.m_handle = nullptr;
    }

    WindowHandle& WindowHandle::operator=(WindowHandle&& other) noexcept
    {
        if (this != &other)
        {
            if (m_handle)
                glfwDestroyWindow(m_handle);

            m_handle              = other.m_handle;
            m_dimensions          = other.m_dimensions;
            m_config              = other.m_config;
            onFramebufferResize   = std::move(other.onFramebufferResize);
            other.m_handle        = nullptr;
        }
        return *this;
    }

    bool WindowHandle::init()
    {
        if (!initGLFW())
            return false;

        m_handle = glfwCreateWindow(
            static_cast<int>(m_config.window.width),
            static_cast<int>(m_config.window.height),
            m_config.window.title.c_str(),
            nullptr,
            nullptr
        );

        if (!m_handle)
        {
            std::cerr << "[WindowHandle] glfwCreateWindow failed\n";
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent(m_handle);

        // Query actual framebuffer size — may differ from window size on HiDPI
        glfwGetFramebufferSize(
            m_handle,
            &m_dimensions.framebufferWidth,
            &m_dimensions.framebufferHeight
        );

        setupCallbacks();
        return true;
    }

    bool WindowHandle::shouldClose() const
    {
        return glfwWindowShouldClose(m_handle);
    }

    void WindowHandle::swapBuffers() const
    {
        glfwSwapBuffers(m_handle);
    }

    void WindowHandle::pollEvents()
    {
        glfwPollEvents();
    }

    GLFWwindow* WindowHandle::handle() const
    {
        return m_handle;
    }

    const Types::Dimensions& WindowHandle::dimensions() const
    {
        return m_dimensions;
    }

    bool WindowHandle::initGLFW()
    {
        if (!glfwInit())
        {
            std::cerr << "[WindowHandle] glfwInit failed\n";
            return false;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, m_config.openGL.versionMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, m_config.openGL.versionMinor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        return true;
    }

    void WindowHandle::setupCallbacks()
    {
        // Store this instance so the static trampoline can reach it.
        // Note: if InputHandle also needs the user pointer, replace this
        // with a shared GlfwUserData struct owned by WindowHandle.
        m_userData.window = this;
        glfwSetWindowUserPointer(m_handle, &m_userData);
        glfwSetFramebufferSizeCallback(m_handle, framebufferSizeCallback);
    }

    // static
    void WindowHandle::framebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        auto* data = static_cast<GlfwUserData*>(glfwGetWindowUserPointer(window));
        if (!data || !data->window)
            return;

        WindowHandle* self = data->window;
        self->m_dimensions.framebufferWidth  = width;
        self->m_dimensions.framebufferHeight = height;

        if (self->onFramebufferResize)
            self->onFramebufferResize(width, height);
    }

} // namespace Platform