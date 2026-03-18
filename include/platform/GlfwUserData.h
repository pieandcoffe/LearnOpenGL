//
// Created by pieandcoffe on 15/03/2026.
//

#ifndef LEARNOPENGL_GLFWUSERDATA_H
#define LEARNOPENGL_GLFWUSERDATA_H


namespace Platform
{
    class WindowHandle;
    class InputHandle;

    struct GlfwUserData
    {
        WindowHandle* window { nullptr };
        InputHandle*  input  { nullptr };
    };
}

#endif // LEARNOPENGL_GLFWUSERDATA_H
