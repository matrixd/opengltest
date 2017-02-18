#include "glfwcontextwrapper.hpp"
#include <mutex>
#include <iostream>
#include "window.hpp"

GLFWContextWrapper::GLFWContextWrapper() :
    m_windowsMutex(*(new std::mutex())),
    m_isInited(false)
{
    init();
}

GLFWContextWrapper::~GLFWContextWrapper()
{
    delete &m_windowsMutex;
}

GLFWContextWrapper &GLFWContextWrapper::inst()
{
    static GLFWContextWrapper g_instance;
    return g_instance;
}

void GLFWContextWrapper::preInit()
{
    static bool g_inited = false;
    if (!g_inited)
    {
        glfwInit();

        glfwSetErrorCallback(GLFWContextWrapper::handleError);

        g_inited = true;
    }
}

void GLFWContextWrapper::registerWindow(GLFWwindow* glfwWindow, Window *window)
{
    inst().m_windowsMutex.lock();
    inst().m_windows[glfwWindow] = window;
    inst().m_windowsMutex.unlock();

    glfwMakeContextCurrent(glfwWindow);
    glfwSetKeyCallback(glfwWindow, GLFWContextWrapper::keyPressedCb);
    glfwSetWindowRefreshCallback(glfwWindow, GLFWContextWrapper::windowRefreshCb);
}

void GLFWContextWrapper::unRegisterWindow(GLFWwindow* glfwWindow)
{
    inst().m_windowsMutex.lock();
    inst().m_windows.erase(glfwWindow);
    inst().m_windowsMutex.unlock();
}

void GLFWContextWrapper::setOpenGLMinorVersion(int version)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, version);
}

void GLFWContextWrapper::setOpenGLMajorVersion(int version)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, version);
}

void GLFWContextWrapper::keyPressedCb(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    GLFWContextWrapper &wrapper = inst();

    wrapper.m_windowsMutex.lock();
    auto it = wrapper.m_windows.find(window);
    if (it != wrapper.m_windows.end())
    {
        it->second->keyPressed(key, scancode, action, mods);
    }
    wrapper.m_windowsMutex.unlock();
}

void GLFWContextWrapper::windowRefreshCb(GLFWwindow *window)
{
    GLFWContextWrapper &wrapper = inst();

    wrapper.m_windowsMutex.lock();
    auto it = wrapper.m_windows.find(window);
    if (it != wrapper.m_windows.end())
    {
        it->second->draw();
    }
    wrapper.m_windowsMutex.unlock();
}

void GLFWContextWrapper::init()
{
    preInit();
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Мы не хотим старый
}

void GLFWContextWrapper::waitForInputEvents()
{
    glfwPollEvents();
}

void GLFWContextWrapper::handleError(int code, const char *descr)
{
    std::cout << "GLFW error was occurred code: " << code << ", " << std::string(descr) << std::endl;
}
