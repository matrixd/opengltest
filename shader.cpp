#include "shader.hpp"
#include <iostream>
#include <array>
#include <memory>

Shader::Shader(GLuint id) :
    m_id(id)
{

}

bool Shader::compile(const Shader::ShaderData &data)
{
    std::array<const GLchar*, 1> ptr{{ data.data() }};
    glShaderSource(m_id, ptr.size(), ptr.data(), NULL);
    glCompileShader(m_id);

    GLint compileStatus;

    glGetShaderiv(m_id, GL_COMPILE_STATUS, &compileStatus);

    if (!compileStatus)
    {
        GLchar log[1024];

        glGetShaderInfoLog(m_id, 512, NULL, log);
        std::cout << "--------------shader compilation error:------------\n" << log;
        std::cout << "----------------------------input:-------------------------\n" << data.data();
        std::cout << std::endl;
    }

    return compileStatus;
}

Shader::~Shader()
{
    if (m_id != 0)
        glDeleteShader(m_id);
}

GLuint Shader::id() const
{
    return m_id;
}

Shader::ShaderPtr Shader::create(int type, const ShaderData &data)
{
    ShaderPtr ptr(new Shader(glCreateShader(type)));
    ptr->compile(data);

    return std::move(ptr);
}
