//
// Created by Kyrylo Pylinskyi on 29/11/2025.
//

#ifndef LEARNOPENGL_DIMENSIONS_HPP
#define LEARNOPENGL_DIMENSIONS_HPP

#include "core/Config.h"

namespace Types
{
    struct Dimensions
    {
        int windowWidth = 0;
        int windowHeight = 0;
        int framebufferWidth = 0;
        int framebufferHeight = 0;

        explicit Dimensions(const Core::WindowConfig& config = {})
            : windowWidth(static_cast<int>(config.width))
            , windowHeight(static_cast<int>(config.height))
            , framebufferWidth(static_cast<int>(config.width))
            , framebufferHeight(static_cast<int>(config.height))
        {}

        [[nodiscard]] float aspectRatio() const
        {
            if (framebufferHeight == 0) return 1.0f;
            return static_cast<float>(framebufferWidth) / static_cast<float>(framebufferHeight);
        }

        [[nodiscard]] float pixelScale() const
        {
            if (windowWidth == 0) return 1.0f;
            return static_cast<float>(framebufferWidth) /
                   static_cast<float>(windowWidth);
        }

        [[nodiscard]] bool isHiDPI() const
        {
            return pixelScale() > 1.0f;
        }
    };
}

#endif // LEARNOPENGL_DIMENSIONS_HPP