#pragma once
#include <GL/glew.h>
#include <cstddef>

using std::size_t;

template <GLenum T> class GLBuffer {
    GLuint m_buffer{};

  public:
    GLBuffer() {
        glGenBuffers(1, &m_buffer);
    }

    ~GLBuffer() { glDeleteBuffers(1, &m_buffer); }

    void bind() const { glBindBuffer(T, m_buffer); }

    void data(const void *data, const size_t size, const GLenum usage) const {
        bind();
        glBufferData(T, size, data, usage);
    }
};