//
// Created by pieandcoffe on 15/03/2026.
//

#ifndef LEARNOPENGL_WINDOW_H
#define LEARNOPENGL_WINDOW_H

#include <functional>
#include <string>

#include "GlfwUserData.h"
#include "core/Config.h"
#include "types/Dimensions.h"

class GLFWwindow;

namespace Platform
{
    /**
     * @brief Manages GLFW window lifecycle.
     *
     * Owns the GLFWwindow handle and is responsible for:
     *   - GLFW initialization and OS window creation
     *   - Framebuffer resize callback and dimension tracking
     *   - Buffer swapping and event polling
     *
     * Intentionally does not own:
     *   - OpenGL context loading (Renderer::Context via handle())
     *   - Input handling (Platform::InputHandle via handle())
     *   - Any GL calls
     */
    class WindowHandle
    {
      public:
        /**
         * @brief Constructs a WindowHandle from an AppConfig.
         *
         * Does not open the window — call init() before using handle().
         *
         * @param config  Runtime config; WindowConfig and OpenGLConfig are consumed here.
         */
        explicit WindowHandle(const Core::AppConfig& config = Core::defaultConfig());

        /**
         * @brief Destroys the GLFW window and calls glfwTerminate().
         */
        ~WindowHandle();

        // GLFW contexts must not be copied
        WindowHandle(const WindowHandle&)            = delete;
        WindowHandle& operator=(const WindowHandle&) = delete;

        // Moving transfers ownership of the GLFW handle
        WindowHandle(WindowHandle&& other) noexcept;
        WindowHandle& operator=(WindowHandle&& other) noexcept;

        /**
         * @brief Initializes GLFW, applies version hints, and opens the OS window.
         *
         * Steps performed:
         *   1. glfwInit()
         *   2. OpenGL version and core profile hints
         *   3. glfwCreateWindow()
         *   4. glfwMakeContextCurrent()
         *   5. Initial framebuffer size query into m_dimensions
         *   6. Framebuffer resize callback registration
         *
         * @return True on success, false on any failure.
         */
        bool init();

        /**
         * @brief Returns true when the user has requested the window to close.
         */
        [[nodiscard]] bool shouldClose() const;

        /**
         * @brief Swaps front and back buffers. Call at the end of each frame.
         */
        void swapBuffers() const;

        /**
         * @brief Polls pending OS and input events. Call once per frame.
         */
        static void pollEvents();

        /**
         * @brief Returns the raw GLFW handle.
         *
         * Pass to Renderer::Context for GLAD init and to
         * Platform::InputHandle for key callback registration.
         * Do not store beyond the lifetime of this WindowHandle.
         */
        [[nodiscard]] GLFWwindow* handle() const;

        /**
         * @brief Returns the current window and framebuffer dimensions.
         *
         * Updated automatically when the framebuffer resize callback fires.
         */
        [[nodiscard]] const Types::Dimensions& dimensions() const;

        /**
         * @brief Fired when the OS resizes the framebuffer.
         *
         * Assign before calling init() so the callback is live from the
         * first resize event. Renderer::Context subscribes here to
         * re-apply glViewport.
         *
         * Signature: void(int framebufferWidth, int framebufferHeight)
         *
         * @code
         *   window.onFramebufferResize = [&ctx](int w, int h) {
         *       ctx.applyViewport(w, h);
         *   };
         * @endcode
         */
        std::function<void(int, int)> onFramebufferResize;

      private:
        GLFWwindow*       m_handle;
        Types::Dimensions m_dimensions;
        Core::AppConfig   m_config;
        GlfwUserData      m_userData;

        /**
         * @brief Calls glfwInit() and sets OpenGL version/profile window hints.
         *
         * Enables forward compatibility for macOS (core profile, no deprecated).
         *
         * @return True if glfwInit() succeeded.
         */
        bool initGLFW();

        /**
         * @brief Stores this instance as the GLFW user pointer and registers callbacks.
         *
         * Uses a GlfwUserData struct as the user pointer so WindowHandle and
         * InputHandle can share it without overwriting each other.
         */
        void setupCallbacks();

        /**
         * @brief GLFW framebuffer resize trampoline (static).
         *
         * Retrieves the WindowHandle instance via glfwGetWindowUserPointer,
         * writes the new size into m_dimensions, then fires onFramebufferResize
         * if a subscriber is set.
         *
         * @param window  GLFW window that was resized.
         * @param width   New framebuffer width in physical pixels.
         * @param height  New framebuffer height in physical pixels.
         */
        static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    };
} // namespace Platform

#endif // LEARNOPENGL_WINDOW_H
