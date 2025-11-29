//
// Created by Kyrylo Pylinskyi on 22/11/2025.
//

#ifndef LEARNOPENGL_WINDOW_H
#define LEARNOPENGL_WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

#include "dimensions.h"
#include "settings.h"

namespace Viewport
{
    /**
     * @brief Handles creation and management of a GLFW window and OpenGL context.
     *
     * The Window class encapsulates GLFW window initialization, input processing,
     * buffer swapping, and resize callbacks. It provides an easy interface for
     * creating a window suitable for OpenGL rendering.
     *
     */
    class Window
    {
      public:
        /**
         * @brief Constructs a Window instance with the desired size and title.
         *
         * @param title  Title displayed in the window's title bar.
         * @param width  Width of the window in logical pixels (default from Settings).
         * @param height Height of the window in logical pixels (default from Settings).
         *
         * @note On HiDPI/Retina displays, the actual framebuffer size may be larger
         *       than the window size (e.g., 2x on Retina displays).
         */
        explicit Window(const char* title, int width = Settings::WINDOW_WIDTH, int height = Settings::WINDOW_HEIGHT);

        /**
         * @brief Destroys the window and cleans up GLFW resources.
         */
        ~Window();

        // Prevent copying (OpenGL contexts shouldn't be copied)
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        // Allow moving
        Window(Window&& other) noexcept;
        Window& operator=(Window&& other) noexcept;

        /**
         * @brief Initializes GLFW, creates the window, and loads OpenGL functions.
         *
         * This method must be called before any rendering can occur. It performs
         * the following steps:
         * 1. Initializes GLFW library
         * 2. Creates the OpenGL context and window
         * 3. Loads OpenGL function pointers via GLAD
         * 4. Sets up resize callbacks
         * 5. Configures the viewport
         *
         * @return True if initialization succeeded, false otherwise.
         */
        bool init();

        /**
         * @brief Checks if the window was requested to close.
         *
         * @return True if the window should close (e.g., user clicked X), false otherwise.
         */
        bool shouldClose() const;

        /**
         * @brief Handles user input (e.g., ESC key to close).
         *
         * This function should be called once per frame in your render loop.
         * Override or extend this method to add custom input handling.
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
         *
         * Call this at the end of each frame after all rendering is complete.
         */
        void swapBuffers() const;

        /**
         * @brief Polls window events such as input, resize, and close events.
         *
         * This should be called once per frame, typically at the end of the render loop.
         */
        static void pollEvents();

        // Getters

        /**
         * @brief Gets the underlying GLFWwindow pointer.
         *
         * @return Raw pointer to the GLFW window. Use with caution.
         */
        GLFWwindow* getGLFWWindow() const;

        /**
         * @brief Gets the viewport dimensions object.
         *
         * @return Reference to the Dimensions object containing window and framebuffer sizes.
         */
        const Dimensions& getDimensions() const;

        /**
         * @brief Returns the current window width in logical pixels.
         *
         * @return Window width (may differ from framebuffer width on HiDPI displays).
         */
        int getWidth() const;

        /**
         * @brief Returns the current window height in logical pixels.
         *
         * @return Window height (may differ from framebuffer height on HiDPI displays).
         */
        int getHeight() const;

        /**
         * @brief Returns the actual framebuffer width in physical pixels.
         *
         * @return Framebuffer width (matches what OpenGL renders to).
         */
        int getFramebufferWidth() const;

        /**
         * @brief Returns the actual framebuffer height in physical pixels.
         *
         * @return Framebuffer height (matches what OpenGL renders to).
         */
        int getFramebufferHeight() const;

        /**
         * @brief Returns the aspect ratio of the framebuffer.
         *
         * @return Aspect ratio (width / height), useful for projection matrices.
         */
        float getAspectRatio() const;

      private:
        GLFWwindow* m_window;    ///< Pointer to the GLFW window.
        Dimensions m_dimensions; ///< Window and framebuffer dimensions.
        std::string m_title;     ///< Title displayed on the window.

        /**
         * @brief Initializes GLFW and configures OpenGL version hints.
         *
         * Sets up OpenGL 3.3 Core Profile with forward compatibility for macOS.
         *
         * @return True if GLFW initialized successfully.
         */
        bool initGLFW();

        /**
         * @brief Loads OpenGL function pointers using GLAD.
         *
         * Must be called after creating the OpenGL context.
         *
         * @return True if GLAD initialized successfully.
         */
        bool initGLAD();

        /**
         * @brief Registers GLFW callback functions.
         *
         * Currently registers the framebuffer resize callback.
         */
        void setupCallbacks();

        /**
         * @brief GLFW callback for handling framebuffer resize events.
         *
         * Automatically updates the OpenGL viewport when the window is resized.
         * This callback receives the framebuffer size, not the window size.
         *
         * @param window GLFW window that triggered the callback.
         * @param width  New width of the framebuffer in pixels.
         * @param height New height of the framebuffer in pixels.
         */
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    };
} // namespace Viewport

#endif // LEARNOPENGL_WINDOW_H