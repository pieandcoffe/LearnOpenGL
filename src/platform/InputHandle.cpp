//
// Created by pieandcoffe on 15/03/2026.
//

#include "platform/InputHandle.h"

#include <iostream>

#include "graphics.h"
#include "platform/GlfwUserData.h"

namespace Platform
{
    InputHandle::InputHandle(GLFWwindow* window)
        : m_window(window)
    {}


    bool InputHandle::init()
    {
        if (!m_window)
        {
            std::cerr << "[InputHandle] init() called with null window handle\n";
            return false;
        }

        // Fetch the GlfwUserData already installed by WindowHandle::setupCallbacks()
        // and register ourselves into it — do NOT overwrite the whole pointer.
        auto* data = static_cast<GlfwUserData*>(glfwGetWindowUserPointer(m_window));
        if (!data)
        {
            std::cerr << "[InputHandle] init() called before WindowHandle::init()\n";
            return false;
        }

        data->input = this;
        glfwSetKeyCallback(m_window, keyCallback);
        return true;
    }

    void InputHandle::bind(int glfwKey, KeyCallback callback)
    {
        m_bindings[glfwKey] = std::move(callback);
    }

    void InputHandle::unbind(int glfwKey)
    {
        m_bindings.erase(glfwKey);
    }

    void InputHandle::pollHeld() const
    {
        for (const auto& [key, callback] : m_bindings)
        {
            if (glfwGetKey(m_window, key) == GLFW_PRESS)
            {
                callback();
            }
        }
    }

    // static
    void InputHandle::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action != GLFW_PRESS)
            return;

        auto* data = static_cast<GlfwUserData*>(glfwGetWindowUserPointer(window));
        if (!data || !data->input)
            return;

        const auto it = data->input->m_bindings.find(key);
        if (it != data->input->m_bindings.end())
            it->second();
    }
} // namespace Platform