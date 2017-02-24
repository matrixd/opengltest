#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
#include <memory>

class Shader
{
public:

    using ShaderData = std::vector<GLchar>;
    using ShaderPtr = std::shared_ptr<Shader>;

    Shader();
    virtual ~Shader();

    GLuint id() const;

    static ShaderPtr create(int type, const ShaderData &data);

private:
    GLuint m_id;

    Shader(GLuint id);
    bool compile(const ShaderData &data);

};

#endif // SHADER_HPP
