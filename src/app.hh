#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct settings {
    bool debug_wireframe = false;
};

class App {
    settings m_settings;
    GLFWwindow *m_glWindow;
    void processInputs();
    void updateWireframeMode() const;
    static void checkGLError();

  public:
    App();
    ~App();
    void run();
};