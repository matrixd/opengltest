#ifndef GLFWCONTEXTWRAPPER_HPP
#define GLFWCONTEXTWRAPPER_HPP

#include <GLFW/glfw3.h>
#include <map>

namespace std {
    class mutex;
}

class Window;

class GLFWContextWrapper
{
public:

    /**
     * @brief registerWindow
     * @param glfwWindow
     * @param window
     *
     * When this function is called - window is automatically set to a current context.
     */
    static void registerWindow(GLFWwindow *glfwWindow, Window *window);
    static void unRegisterWindow(GLFWwindow *glfwWindow);

    static void setOpenGLMinorVersion(int version);
    static void setOpenGLMajorVersion(int version);

    static void init();

    static void waitForInputEvents();

private:
    std::map<GLFWwindow*, Window*> m_windows;
    std::mutex &m_windowsMutex;
    bool m_isInited;

    GLFWContextWrapper();
    ~GLFWContextWrapper();
    static void handleError(int code, const char *descr);
    static void keyPressedCb(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void windowRefreshCb(GLFWwindow *window);
    static GLFWContextWrapper &inst();
    static void preInit();

};

#endif // GLFWCONTEXTWRAPPER_HPP
