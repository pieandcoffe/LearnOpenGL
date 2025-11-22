//
// Created by Kyrylo Pylinskyi on 22/11/2025.
//

#ifndef LEARNOPENGL_WINDOW_H
#define LEARNOPENGL_WINDOW_H

#include <string>
#include <GLFW/glfw3.h>

/**
 * @brief Handles creation and management of a GLFW window and OpenGL context.
 *
 * The Window class encapsulates GLFW window initialization, input processing,
 * buffer swapping, and resize callbacks. It provides an easy interface for
 * creating a window suitable for OpenGL rendering.
 */
class Window {
public:

    /**
     * @brief Constructs a Window instance with the desired size and title.
     *
     * @param width  Width of the window in pixels.
     * @param height Height of the window in pixels.
     * @param title  Title displayed in the window's title bar.
     */
    Window(int width, int height, const char* title);

    /**
     * @brief Destroys the window and cleans up GLFW resources.
     */
    ~Window();

    /**
     * @brief Initializes GLFW, creates the window, and loads OpenGL functions.
     *
     * @return True if initialization succeeded, false otherwise.
     */
    bool init();

    /**
     * @brief Checks if the window was requested to close.
     *
     * @return True if the window should close, false otherwise.
     */
    bool shouldClose() const;

    /**
     * @brief Handles user input (e.g., ESC key to close).
     *
     * This function is intended to be called once per frame.
     */
    void processInput() const;

    /**
     * @brief Clears the screen using the specified RGBA color.
     *
     * @param r Red component   (0.0f to 1.0f)
     * @param g Green component (0.0f to 1.0f)
     * @param b Blue component  (0.0f to 1.0f)
     * @param a Alpha component (0.0f to 1.0f)
     */
    static void clear(float r, float g, float b, float a);

    /**
     * @brief Swaps the front and back buffers.
     */
    void swapBuffers() const;

    /**
     * @brief Polls window events such as input or resize events.
     */
    static void pollEvents();

    /**
     * @brief Gets the underlying GLFWwindow pointer.
     *
     * @return Raw pointer to the GLFW window.
     */
    GLFWwindow* getGLFWWindow() const;

    /**
     * @brief Returns the current window width in pixels.
     */
    int getWidth() const;

    /**
     * @brief Returns the current window height in pixels.
     */
    int getHeight() const;

private:
    GLFWwindow* m_window;   ///< Pointer to the GLFW window.
    int m_width;            ///< Window width in pixels.
    int m_height;           ///< Window height in pixels.
    std::string m_title;    ///< Title displayed on the window.

    /**
     * @brief Initializes GLFW and configures version hints.
     *
     * @return True if GLFW initialized successfully.
     */
    bool initGLFW();

    /**
     * @brief Loads OpenGL function pointers using GLAD.
     *
     * @return True if GLAD initialized successfully.
     */
    bool initGLAD() const;

    /**
     * @brief Registers GLFW callback functions (e.g., framebuffer resize).
     */
    void setupCallbacks() const;

    /**
     * @brief GLFW callback for handling window resize events.
     *
     * @param window GLFW window that triggered the callback.
     * @param width  New width of the framebuffer.
     * @param height New height of the framebuffer.
     */
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

#endif // LEARNOPENGL_WINDOW_H
