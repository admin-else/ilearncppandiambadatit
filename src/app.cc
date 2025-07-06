#include "app.hh"
#include "buffer.hh"
#include "consts.hh"
#include "error.hh"
#include "buffer.hh"
#include "shader.hh"
#include "vao.hh"
#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>

using glm::vec3;
constexpr float vertices[] = {
    0.5f,  0.5f,  0.0f, // top right
    0.5f,  -0.5f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f, // bottom left
    -0.5f, 0.5f,  0.0f  // top left
};
constexpr unsigned int indices[] = {
    // note that we start from 0!
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};
static void errorCallback(int code, const char *message) {
    throw GameError(message);
}

static void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void App::updateWireframeMode() const {
    glPolygonMode(GL_FRONT_AND_BACK,
                  m_settings.debug_wireframe ? GL_LINE : GL_FILL);
}

void App::processInputs() {
    if (glfwGetKey(m_glWindow, GLFW_KEY_F3) == GLFW_PRESS) {
        m_settings.debug_wireframe = !m_settings.debug_wireframe;
        updateWireframeMode();
    }
    if (glfwGetKey(m_glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_glWindow, GLFW_TRUE);
}

void App::checkGLError() {
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw GameError(
            string(reinterpret_cast<const char *>(gluErrorString(error))));
    }
}

void App::run() {
    const Vao vao;
    vao.bind();
    const GLBuffer<GL_ARRAY_BUFFER> vbo;
    vbo.data(&vertices, sizeof(vertices), GL_STATIC_DRAW);

    const GLBuffer<GL_ELEMENT_ARRAY_BUFFER> ebo;
    ebo.data(&indices, sizeof(indices), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), static_cast<void *>(nullptr));
    glEnableVertexAttribArray(0);

    const Shader shader("tri");

    while (!glfwWindowShouldClose(m_glWindow)) {
        processInputs();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        glfwSwapBuffers(m_glWindow);
        glfwPollEvents();
        checkGLError();
    }
}

App::App() {
    glfwSetErrorCallback(errorCallback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_glWindow =
        glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "game", nullptr, nullptr);
    glfwMakeContextCurrent(m_glWindow);
    glfwSetFramebufferSizeCallback(m_glWindow, framebufferSizeCallback);
    glewInit();
}

App::~App() { glfwTerminate(); }