#pragma once

#include <GL/glew.h>

template <GLenum target> class Texture {
public:
    GLuint m_texure;
    Texture() {
        glGenTextures(1, &m_texure);
    }

    void bind() {
        glBindTexture(target, m_texure);
    }   
};