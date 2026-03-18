//
// Created by pieandcoffe on 15/03/2026.
//

#ifndef LEARNOPENGL_INPUTHANDLER_H
#define LEARNOPENGL_INPUTHANDLER_H


#include <functional>
#include <unordered_map>

class GLFWwindow;

namespace Platform
{
    /**
     * @brief Maps GLFW key events to application-level callbacks.
     *
     * Two dispatch paths:
     *   - Event-driven: keyCallback fires on GLFW_PRESS / GLFW_RELEASE.
     *     Use bind() for discrete actions (quit, toggle wireframe, screenshot).
     *   - Polled: pollHeld() queries glfwGetKey every frame.
     *     Use for held keys that need continuous response (camera movement).
     *
     * Both paths share the same m_bindings table so bind() / unbind()
     * affect both dispatch modes consistently.
     */
    class InputHandle
    {
      public:
        using KeyCallback = std::function<void()>;

        /**
         * @brief Constructs an InputHandle for the given GLFW window.
         *
         * Does not register the GLFW callback — call init() after bind().
         *
         * @param window  Live GLFW handle from Platform::Window::handle().
         */
        explicit InputHandle(GLFWwindow* window);

        /**
         * @brief Registers the GLFW key callback with the window.
         *
         * Must be called after all bind() calls so the binding table
         * is fully populated before any key events arrive.
         *
         * Stores a pointer to this instance as the GLFW window user pointer
         * so the static keyCallback trampoline can reach it.
         *
         * @return True if the window handle is valid and registration succeeded.
         */
        bool init();

        /**
         * @brief Binds a callback to a GLFW key code.
         *
         * Fires on GLFW_PRESS via the event callback, and on every frame
         * the key is held via pollHeld(). Rebinding an existing key replaces
         * the previous callback silently.
         *
         * @param glfwKey   GLFW key constant (e.g. GLFW_KEY_ESCAPE).
         * @param callback  Function to invoke when the key is active.
         */
        void bind(int glfwKey, KeyCallback callback);

        /**
         * @brief Removes the binding for the given key, if any.
         *
         * Safe to call for keys that were never bound.
         *
         * @param glfwKey  GLFW key constant to unbind.
         */
        void unbind(int glfwKey);

        /**
         * @brief Polls all bound keys via glfwGetKey and fires callbacks.
         *
         * Call once per frame for held-key behaviour (movement, zoom, etc.).
         * Only fires callbacks for keys currently in GLFW_PRESS state.
         */
        void pollHeld() const;

      private:
        GLFWwindow*                          m_window;
        std::unordered_map<int, KeyCallback> m_bindings;

        /**
         * @brief GLFW key event callback (static trampoline).
         *
         * Retrieves the InputHandle instance via glfwGetWindowUserPointer
         * and dispatches to the matching entry in m_bindings on GLFW_PRESS.
         *
         * @param window    GLFW window that received the event.
         * @param key       GLFW key constant.
         * @param scancode  Platform scancode (unused).
         * @param action    GLFW_PRESS, GLFW_RELEASE, or GLFW_REPEAT.
         * @param mods      Modifier key bitmask (unused).
         */
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    };

} // namespace Platform

#endif // LEARNOPENGL_INPUTHANDLER_H
