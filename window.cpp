#include "window.hpp"

#include <iostream>
#include <condition_variable>

#include "glfwcontextwrapper.hpp"

Window::Window() :
    Window(1024, 768)
{

}

Window::Window(int width, int height, std::string &&title)
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
    glClearColor(0.2,
    0.3,
    0.3,
    1.0);

    glClear(GL_COLOR_BUFFER_BIT);
    // Define the viewport dimensions
    int width, height;
    glfwGetFramebufferSize(m_window, &width, &height);
    glViewport(0, 0, width, height);
    //glBindVertexArray(0);


    for (auto &function : m_drawSteps)
    {
        function();
    }

    glfwSwapBuffers(m_window);
}

void Window::addDrawStep(Window::DrawFunction step)
{
    m_drawSteps.push_back(step);
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
