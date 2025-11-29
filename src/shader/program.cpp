//
// Created by Kyrylo Pylinskyi on 22/11/2025.
//

#include "shader/program.h"

#include <iostream>

#include "shader/stage.h"

ShaderProgram::ShaderProgram()
{
    m_id = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    if (m_id != 0)
    {
        glDeleteProgram(m_id);
    }
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept
    : m_id(other.m_id)
{
    other.m_id = 0;
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept
{
    if (this != &other)
    {
        glDeleteProgram(m_id);
        m_id = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

void ShaderProgram::attach(const ShaderStage& stage) const
{
    glAttachShader(m_id, stage.getID());
}

bool ShaderProgram::link() const
{
    glLinkProgram(m_id);

    int success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_id, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Failed to link program: " + std::string(infoLog) << std::endl;
        return false;
    }
    return true;
}

void ShaderProgram::bind() const
{
    glUseProgram(m_id);
}

void ShaderProgram::unbind() const
{
    glUseProgram(0);
}

GLuint ShaderProgram::getId() const
{
    return m_id;
}

void ShaderProgram::setUniform(const std::string& name, int value)
{
    /// TODO
}

void ShaderProgram::setUniform(const std::string& name, float value)
{
    /// TODO
}

void ShaderProgram::setUniform(const std::string& name, const glm::mat4& mat4)
{
    /// TODO
}
