#include <GL/glew.h>
#include <cstddef>

using std::size_t;

class GLBuffer {
    GLuint m_vbo;
    GLenum m_btype;
public:
    GLBuffer(GLenum type) {
        m_btype = type;
        glGenBuffers(1, &m_vbo);
    }

    ~GLBuffer() {
        glDeleteBuffers(1, &m_vbo);
    }
    
    inline void bind() {
        glBindBuffer(m_btype, m_vbo);
    }

    inline void data(const void *data, size_t size, GLenum usage) {
        bind();
        glBufferData(m_btype, size, data, usage);
    }
};