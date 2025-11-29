//
// Created by Kyrylo Pylinskyi on 22/11/2025.
//

#ifndef LEARNOPENGL_SHADER_PROGRAM_H
#define LEARNOPENGL_SHADER_PROGRAM_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "glad/glad.h"

class ShaderStage;

class ShaderProgram
{
  public:
    ShaderProgram();
    ~ShaderProgram();

    ShaderProgram(const ShaderProgram& other) = delete;
    ShaderProgram& operator=(const ShaderProgram& other) = delete;

    ShaderProgram(ShaderProgram&& other) noexcept;
    ShaderProgram& operator=(ShaderProgram&& other) noexcept;

    void attach(const ShaderStage& stage) const;
    bool link() const;

    void bind() const;
    void unbind() const;

    GLuint getId() const;

    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, const glm::mat4& mat4);

  private:
    GLuint m_id;
};

#endif // LEARNOPENGL_SHADER_PROGRAM_H