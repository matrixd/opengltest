#include <iostream>
#include <GL/glew.h>
#include <unistd.h>
#include "glfwcontextwrapper.hpp"
#include "window.hpp"

int main(int argc, char *argv[])
{
    GLFWContextWrapper::init();

    GLFWContextWrapper::setOpenGLMinorVersion(2);
    GLFWContextWrapper::setOpenGLMajorVersion(3);

    Window *w = new Window();

    glewExperimental=true; // Флаг необходим в Core-режиме OpenGL
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Невозможно инициализировать GLEWn");
        return -1;
    }


    w->run();
    return 0;
}
