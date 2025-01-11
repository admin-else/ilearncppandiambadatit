#include "app.hh"
#include "consts.hh"
#include "error.hh"
#include "glbuffer.hh"
#include "shader.hh"
#include "vao.hh"
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

static void frambufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void App::updateWireframeMode() {
    glPolygonMode(GL_FRONT_AND_BACK,
                  m_settings.debug_wireframe ? GL_LINE : GL_FILL);
}

void App::processInputs() {
    if (glfwGetKey(m_glWinodw, GLFW_KEY_F3) == GLFW_PRESS) {
        m_settings.debug_wireframe = !m_settings.debug_wireframe;
        updateWireframeMode();
    }
    if (glfwGetKey(m_glWinodw, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_glWinodw, GLFW_TRUE);
}

void App::checkGLError() {
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        throw GameError(
            string(reinterpret_cast<const char *>(gluErrorString(error))));
    }
}

void App::run() {
    Vao vao;
    vao.bind();
    GLBuffer vbo(GL_ARRAY_BUFFER);
    vbo.data(&vertices, sizeof(vertices), GL_STATIC_DRAW);
    GLBuffer ebo(GL_ELEMENT_ARRAY_BUFFER);
    ebo.data(&indices, sizeof(indices), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void *)0);
    glEnableVertexAttribArray(0);

    Shader shader("tri");

    while (!glfwWindowShouldClose(m_glWinodw)) {
        processInputs();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(m_glWinodw);
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
    m_glWinodw =
        glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "game", nullptr, nullptr);
    glfwMakeContextCurrent(m_glWinodw);
    glfwSetFramebufferSizeCallback(m_glWinodw, frambufferSizeCallback);
    glewInit();
}

App::~App() { glfwTerminate(); }