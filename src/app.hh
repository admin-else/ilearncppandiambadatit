#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct settings {
    bool debug_wireframe = false;
};

class App {
  private:
    struct settings m_settings;
    GLFWwindow *m_glWinodw;
    void processInputs();
    void updateWireframeMode();
    void checkGLError();

  public:
    App();
    ~App();
    void run();
};