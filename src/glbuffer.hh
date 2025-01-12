#include <GL/glew.h>
#include <cstddef>

using std::size_t;

template <GLenum T> class GLBuffer {
    GLuint m_buffer;

  public:
    GLBuffer() {
        glGenBuffers(1, &m_buffer);
    }

    ~GLBuffer() { glDeleteBuffers(1, &m_buffer); }

    inline void bind() { glBindBuffer(T, m_buffer); }

    inline void data(const void *data, size_t size, GLenum usage) {
        bind();
        glBufferData(T, size, data, usage);
    }
};