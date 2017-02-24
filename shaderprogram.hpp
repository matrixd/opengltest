#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include "shader.hpp"

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    void attachShader(Shader::ShaderPtr &shader);

    void link();
    void use();

    bool isLinked() const;

private:
    GLuint m_id;
    std::vector<Shader::ShaderPtr> m_shaders;
    bool m_linked;
};

#endif // SHADERPROGRAM_HPP
