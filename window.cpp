#include "window.hpp"

#include <iostream>
#include <condition_variable>

#include "glfwcontextwrapper.hpp"

Window::Window() :
    Window(1024, 768)
{

}

Window::Window(int width, int height, const std::string &&title)
{
    m_title = title;
    m_window = glfwCreateWindow(width, height, m_title.c_str(), NULL, NULL);
    GLFWContextWrapper::registerWindow(m_window, this);
}

Window::~Window()
{
    GLFWContextWrapper::unRegisterWindow(m_window);
}

void Window::keyPressed(int key, int scancode, int action, int mods)
{
    std::cout << "receive key event window: " << m_title << "keycode: " << key << std::endl;
}

void Window::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    //draw goes here
    glfwSwapBuffers(m_window);
}

std::string Window::title() const
{
    return m_title;
}

void Window::run()
{
    m_stillRunning = 1;
    while (m_stillRunning && !glfwWindowShouldClose(m_window))
    {
        glfwPollEvents();
    }
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_window);
}
