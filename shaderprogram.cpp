#include "shaderprogram.hpp"
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

ShaderProgram::ShaderProgram() :
    m_id(glCreateProgram()),
    m_shaders(2)
{
}

ShaderProgram::~ShaderProgram()
{

}

void ShaderProgram::attachShader(Shader::ShaderPtr &shader)
{
    glAttachShader(m_id, shader->id());
    m_shaders.push_back(shader);
}

void ShaderProgram::link()
{
    glLinkProgram(m_id);

    GLint success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar log[512];
        glGetProgramInfoLog(m_id, 512, NULL, log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
    }
    m_linked = true;
}

void ShaderProgram::use()
{
    glUseProgram(m_id);
}

bool ShaderProgram::isLinked() const
{
    return m_linked;
}

