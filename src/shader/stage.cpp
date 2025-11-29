//
// Created by Kyrylo Pylinskyi on 22/11/2025.
//

#include "shader/stage.h"

#include <fstream>
#include <sstream>
#include <utility>

ShaderStage::ShaderStage(std::string filepath, const GLenum type)
    : m_id(0)
    , m_type(type)
    , m_filepath(std::move(filepath))
{
    const std::string source = loadShaderSource();
    compile(source);
}

ShaderStage::~ShaderStage()
{
    if (m_id != 0)
    {
        glDeleteShader(m_id);
    }
}

ShaderStage::ShaderStage(ShaderStage&& other) noexcept
    : m_id(0)
    , m_type(other.m_type)
    , m_filepath(std::move(other.m_filepath))
{
    other.m_id = 0;
}

ShaderStage& ShaderStage::operator=(ShaderStage&& other) noexcept
{
    if (this != &other)
    {
        glDeleteShader(m_id);
        m_id = other.m_id;
        m_type = other.m_type;
        m_filepath = std::move(other.m_filepath);
        other.m_id = 0;
    }
    return *this;
}

GLuint ShaderStage::getID() const
{
    return m_id;
}

GLenum ShaderStage::getType() const
{
    return m_type;
}

std::string ShaderStage::loadShaderSource() const
{
    std::ifstream file(m_filepath);
    std::stringstream buffer;

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file " + m_filepath);
    }

    buffer << file.rdbuf();
    return buffer.str();
}

void ShaderStage::compile(const std::string& source)
{
    const char* sourceCString = source.c_str();
    m_id = glCreateShader(m_type);
    glShaderSource(m_id, 1, &sourceCString, nullptr);
    glCompileShader(m_id);

    int success;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(m_id, 512, nullptr, infoLog);
        throw std::runtime_error("Failed to compile (" + m_filepath + "): " + std::string(infoLog));
    }
}
