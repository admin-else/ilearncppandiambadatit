#pragma once

#include <GL/glew.h>

class Vao {
    GLuint m_vao{};

  public:
    void bind() const { glBindVertexArray(m_vao); }
    static void unbind() { glBindVertexArray(0); }

    Vao() { glGenVertexArrays(1, &m_vao); }
    ~Vao() { glDeleteVertexArrays(1, &m_vao); }
};