//
// Created by pieandcoffe on 15/03/2026.
//

#ifndef LEARNOPENGL_APPLICATION_H
#define LEARNOPENGL_APPLICATION_H
#include <memory>

#include "core/Config.h"
#include "platform/InputHandle.h"
#include "platform/Window.h"

namespace Core
{
    class Application
    {
      public:
        explicit Application(const AppConfig& config = defaultAppConfig());

        ~Application();

        Application(const Application&) = delete;
        Application& operator=(const Application&) = delete;

        bool init();

        void run();

      private:
        AppConfig                              m_config;
        Platform::WindowHandle                       m_window;
        std::unique_ptr<Platform::InputHandle> m_input;

        unsigned int m_VAO = 0;
        unsigned int m_VBO = 0;

        void initGeometry();

        bool initShaders();

        void bindInput();

        void draw() const;
    };
} // namespace Core

#endif // LEARNOPENGL_APPLICATION_H
