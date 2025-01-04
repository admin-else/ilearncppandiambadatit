#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class App {
  private:
    GLFWwindow *m_glWinodw;
    void processInputs();
    void checkGLError();

  public:
    App();
    ~App();
    void run();
};