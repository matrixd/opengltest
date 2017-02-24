#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <unistd.h>
#include <vector>
#include <string>
#include "glfwcontextwrapper.hpp"
#include "window.hpp"
#include "shader.hpp"
#include "shaderprogram.hpp"

int main(int argc, char *argv[])
{

    GLFWContextWrapper::init();
    GLFWContextWrapper::setOpenGLMajorVersion(3);
    GLFWContextWrapper::setOpenGLMinorVersion(2);

    Window *w = new Window();

    glewExperimental=true; // Флаг необходим в Core-режиме OpenGL
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Невозможно инициализировать GLEWn");
        return -1;
    }


    std::string tmp("#version 330 core\n\
 \
layout (location = 0) in vec3 position;\n\
\
void main()\n\
{\n\
    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n\
}" );
    Shader::ShaderData vdata(tmp.begin(), tmp.end());
    vdata.push_back(0);

    std::array<GLfloat, 9> vertices({
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    });

    auto vertex = Shader::create(GL_VERTEX_SHADER, vdata);

    tmp = "#version 330 core\n\
out vec4 color;\n\
void main()\n\
{\n\
    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n\
}";

    Shader::ShaderData fdata(tmp.begin(), tmp.end());
    fdata.push_back(0);

    auto fragment = Shader::create(GL_FRAGMENT_SHADER, fdata);

    ShaderProgram prgrm;
    prgrm.attachShader(vertex);
    prgrm.attachShader(fragment);

    prgrm.link();

    GLuint VAO;
    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)



    w->addDrawStep([&](){
    prgrm.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    });

    w->draw();
    w->run();
    return 0;
}
