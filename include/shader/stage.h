//
// Created by Kyrylo Pylinskyi on 22/11/2025.
//

#ifndef LEARNOPENGL_SHADER_STAGE_H
#define LEARNOPENGL_SHADER_STAGE_H

#include <string>

#include "glad/glad.h"

class ShaderStage
{
  public:
    ShaderStage(std::string filepath, GLenum type);
    ~ShaderStage();

    ShaderStage(const ShaderStage&) = delete;
    ShaderStage& operator=(const ShaderStage&) = delete;

    ShaderStage(ShaderStage&&) noexcept;
    ShaderStage& operator=(ShaderStage&&) noexcept;

    GLuint getID() const;
    GLenum getType() const;

  private:
    GLuint m_id;
    GLenum m_type;
    std::string m_filepath;

    std::string loadShaderSource() const;
    void compile(const std::string& source);
};

#endif // LEARNOPENGL_SHADER_STAGE_H