#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>

struct GLFWwindow;
namespace std {
    class condition_variable;
}

class Window
{
public:
    Window();
    Window(int width, int height, const std::__cxx11::string &&title = std::string("new window"));
    virtual ~Window();

    virtual void keyPressed(int key, int scancode, int action, int mods);
    virtual void draw();

    std::string title() const;

    void run();
    void stop();

protected:

private:
    GLFWwindow *m_window;
    std::string m_title;
    volatile int m_stillRunning;

    void swapBuffers();
};

#endif // WINDOW_HPP
