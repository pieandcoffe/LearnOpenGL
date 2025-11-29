#include <vector>

#include "shader/program.h"
#include "shader/stage.h"
#include "viewport/settings.h"
#include "viewport/window.h"

int main()
{
    // Create window
    Viewport::Window window(Settings::WINDOW_TITLE);

    if (!window.init())
    {
        return -1;
    }

    std::vector vertices = {
        -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f,

        -0.5f, 0.5f,  0.0f, 0.5f, -0.5f, 0.0f, 0.5f,  0.5f, 0.0f,
    };

    // === VAO ===
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // === VBO ===
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // === SHADERS ===
    const ShaderStage vert("shaders/basic.vert", GL_VERTEX_SHADER);
    const ShaderStage frag("shaders/basic.frag", GL_FRAGMENT_SHADER);

    ShaderProgram program;
    program.attach(vert);
    program.attach(frag);

    if (!program.link())
    {
        return -1;
    }

    // === Render loop ===
    while (!window.shouldClose())
    {
        window.processInput();

        window.clear(Settings::CLEAR_COLOR_R, Settings::CLEAR_COLOR_G, Settings::CLEAR_COLOR_B,
                     Settings::CLEAR_COLOR_A);

        program.bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        window.swapBuffers();
        window.pollEvents();
    }

    return 0;
}
