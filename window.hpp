#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <vector>
#include <functional>

struct GLFWwindow;
namespace std {
    class condition_variable;
}

class Window
{
public:
    using DrawFunction = std::function<void()>;

    Window();
    Window(int width, int height, std::__cxx11::string &&title = std::string("new window"));
    virtual ~Window();

    virtual void keyPressed(int key, int scancode, int action, int mods);
    virtual void draw();

    void addDrawStep(DrawFunction step);

    std::string title() const;

    void run();
    void stop();

protected:

private:
    GLFWwindow *m_window;
    std::string m_title;
    volatile int m_stillRunning;

    std::vector<DrawFunction> m_drawSteps;

    void swapBuffers();
};

#endif // WINDOW_HPP
