#pragma once

#include <GL/glew.h>
#include <string>

#include <GL/gl.h>
using std::string;

class Shader {
  private:
    GLuint m_programm;
    GLuint compileShader(string path, GLenum type);

  public:
    void use();
    Shader(const string &path);
    ~Shader();
};