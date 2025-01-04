#include "shader.hh"
#include "consts.hh"
#include "error.hh"
#include <GL/gl.h>
#include <fstream>
#include <iterator>
#include <string>

using std::string, std::ifstream, std::istreambuf_iterator;

static string readfile(const string &path) {
    ifstream file;
    file.exceptions(ifstream::failbit | ifstream::badbit);
    file.open(path);
    return string((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());
}

GLuint Shader::compileShader(string path, GLenum type) {
    auto shader = glCreateShader(type);
    auto src = readfile(path);
    auto srcLen = src.length();
    auto srcCStr = src.c_str();
    glShaderSource(shader, 1, &srcCStr, nullptr);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[ERROR_LOG_LEN];
        glGetShaderInfoLog(shader, ERROR_LOG_LEN, nullptr, info);
        throw GameError(string(info));
    }
    return shader;
}

void Shader::use() { glUseProgram(m_programm); }

Shader::Shader(const string &name) {
    auto vertexShader =
        compileShader("assets/shader/" + name + ".vert", GL_VERTEX_SHADER);
    auto fragmentShader =
        compileShader("assets/shader/" + name + ".frag", GL_FRAGMENT_SHADER);

    m_programm = glCreateProgram();
    glAttachShader(m_programm, vertexShader);
    glAttachShader(m_programm, fragmentShader);

    glLinkProgram(m_programm);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int success;
    glGetProgramiv(m_programm, GL_LINK_STATUS, &success);
    if (!success) {
        char info[ERROR_LOG_LEN];
        glGetProgramInfoLog(m_programm, ERROR_LOG_LEN, nullptr, info);
        throw GameError(string(info));
    }
}

Shader::~Shader() {
    glDeleteProgram(m_programm);
}