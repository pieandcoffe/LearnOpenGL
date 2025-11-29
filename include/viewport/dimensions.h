//
// Created by Kyrylo Pylinskyi on 29/11/2025.
//

#ifndef LEARNOPENGL_DIMENSIONS_HPP
#define LEARNOPENGL_DIMENSIONS_HPP

#include <GLFW/glfw3.h>

#include "viewport/settings.h"

namespace Viewport
{
    class Dimensions
    {
      public:
        explicit Dimensions(const int windowWidth = Settings::WINDOW_WIDTH,
                            const int windowHeight = Settings::WINDOW_HEIGHT)
            : m_windowWidth(windowWidth)
            , m_windowHeight(windowHeight)
            , m_framebufferWidth(windowWidth)
            , m_framebufferHeight(windowHeight)
        {
        }

        // Getters
        int getWindowWidth() const;
        int getWindowHeight() const;
        int getBufferWidth() const;
        int getBufferHeight() const;

        // Helper methods
        float getAspectRatio() const;
        float getPixelScale() const;
        bool isHiDPI() const;

        // Update and apply
        void updateFromWindow(GLFWwindow* window);
        void applyViewport() const;

      private:
        int m_windowWidth;
        int m_windowHeight;
        int m_framebufferWidth;
        int m_framebufferHeight;
    };
} // namespace Viewport

#endif // LEARNOPENGL_DIMENSIONS_HPP