//
// Created by Kyrylo Pylinskyi on 22/11/2025.
//

#ifndef LEARNOPENGL_CONFIG_H
#define LEARNOPENGL_CONFIG_H

/**
 * @brief Global engine/application settings.
 *
 * Provides compile-time configuration related to the window,
 * OpenGL context, and clear color values.
 */
struct Settings
{
    // -----------------------------
    // Window settings
    // -----------------------------

    /** @brief Width of the application window in pixels. */
    static constexpr unsigned int WINDOW_WIDTH = 600;

    /** @brief Height of the application window in pixels. */
    static constexpr unsigned int WINDOW_HEIGHT = 400;

    /** @brief Title of the window shown in the title bar. */
    static constexpr const char* WINDOW_TITLE = "LearnOpenGL";

    // -----------------------------
    // OpenGL settings
    // -----------------------------

    /** @brief Major version of the OpenGL context to create. */
    static constexpr int OPENGL_VERSION_MAJOR = 3;

    /** @brief Minor version of the OpenGL context to create. */
    static constexpr int OPENGL_VERSION_MINOR = 3;

    // -----------------------------
    // Clear color settings
    // -----------------------------

    /** @brief Red component of the default clear color (0.0–1.0). */
    static constexpr float CLEAR_COLOR_R = 0.21f;

    /** @brief Green component of the default clear color (0.0–1.0). */
    static constexpr float CLEAR_COLOR_G = 0.61f;

    /** @brief Blue component of the default clear color (0.0–1.0). */
    static constexpr float CLEAR_COLOR_B = 0.61f;

    /** @brief Alpha component of the default clear color (0.0–1.0). */
    static constexpr float CLEAR_COLOR_A = 1.0f;
};

#endif // LEARNOPENGL_CONFIG_H
