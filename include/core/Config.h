//
// Created by pieandcoffe on 15/03/2026.
//

#ifndef LEARNOPENGL_CONFIG_H
#define LEARNOPENGL_CONFIG_H

#include <string>

namespace Core
{
    /**
     * @brief Window creation and display settings.
     */
    struct WindowConfig
    {
        unsigned int width  = 800;
        unsigned int height = 600;
        std::string  title  = "KRender";
    };

    /**
     * @brief OpenGL context version settings.
     */
    struct OpenGLConfig
    {
        int versionMajor = 3;
        int versionMinor = 3;
    };

    /**
     * @brief Renderer clear color as normalized RGBA components (0.0–1.0).
     */
    struct ClearColorConfig
    {
        float r = 0.21f;
        float g = 0.21f;
        float b = 0.21f;
        float a = 1.0f;
    };

    /**
     * @brief Aggregated runtime application configuration.
     *
     * Passed by value into subsystems that need it. Construct directly
     * to override individual fields:
     * @code
     *   Core::AppConfig cfg;
     *   cfg.window.width  = 1280;
     *   cfg.window.height = 720;
     *   cfg.window.title  = "My App";
     * @endcode
     */
    struct AppConfig
    {
        WindowConfig     window;
        OpenGLConfig     openGL;
        ClearColorConfig clearColor;
    };

    /**
     * @brief Returns a default-constructed AppConfig.
     *
     * Use as the fallback when no config file is present.
     * Named defaultConfig() — the return type already conveys it's an AppConfig.
     */
    inline AppConfig defaultConfig()
    {
        return AppConfig{};
    }

} // namespace Core

#endif // LEARNOPENGL_CONFIG_H
