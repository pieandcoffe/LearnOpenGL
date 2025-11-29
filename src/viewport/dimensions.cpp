//
// Created by Kyrylo Pylinskyi on 29/11/2025.
//

#include "viewport/dimensions.h"

#include <glad/glad.h>

namespace Viewport
{
    // Getters
    int Dimensions::getWindowWidth() const
    {
        return m_windowWidth;
    }

    int Dimensions::getWindowHeight() const
    {
        return m_windowHeight;
    }

    int Dimensions::getBufferWidth() const
    {
        return m_framebufferWidth;
    }

    int Dimensions::getBufferHeight() const
    {
        return m_framebufferHeight;
    }

    // Helper methods
    float Dimensions::getAspectRatio() const
    {
        // Avoid division by zero
        if (m_framebufferHeight == 0)
        {
            return 1.0f;
        }

        return static_cast<float>(m_framebufferWidth) / static_cast<float>(m_framebufferHeight);
    }

    float Dimensions::getPixelScale() const
    {
        // Avoid division by zero
        if (m_windowWidth == 0)
        {
            return 1.0f;
        }

        return static_cast<float>(m_framebufferWidth) / static_cast<float>(m_windowWidth);
    }

    bool Dimensions::isHiDPI() const
    {
        // Check if framebuffer dimensions differ from window dimensions
        return m_framebufferWidth != m_windowWidth || m_framebufferHeight != m_windowHeight;
    }

    // Update and apply
    void Dimensions::updateFromWindow(GLFWwindow* window)
    {
        if (window == nullptr)
        {
            return;
        }

        // Get current window size (logical pixels)
        glfwGetWindowSize(window, &m_windowWidth, &m_windowHeight);

        // Get current framebuffer size (physical pixels)
        glfwGetFramebufferSize(window, &m_framebufferWidth, &m_framebufferHeight);
    }

    void Dimensions::applyViewport() const
    {
        // Set OpenGL viewport to match framebuffer dimensions
        glViewport(0, 0, m_framebufferWidth, m_framebufferHeight);
    }

} // namespace Viewport