#include "window.h"
#include "settings.h"

int main() {
    // Create window
    Window window(Settings::WINDOW_WIDTH, Settings::WINDOW_HEIGHT, Settings::WINDOW_TITLE);

    if (!window.init()) {
        return -1;
    }

    // Render loop
    while (!window.shouldClose()) {
        // Process input
        window.processInput();

        // Render
        Window::clear(Settings::CLEAR_COLOR_R, Settings::CLEAR_COLOR_G, Settings::CLEAR_COLOR_B, Settings::CLEAR_COLOR_A);



        // Swap buffers and poll events
        window.swapBuffers();
        Window::pollEvents();
    }

    return 0;
}