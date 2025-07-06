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
    return {(istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>()};
}

GLuint Shader::compileShader(const string& path, const GLenum type) {
    const auto shader = glCreateShader(type);
    const auto src = readfile(path);
    const auto srcCStr = src.c_str();
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

void Shader::use() const { glUseProgram(m_program); }

Shader::Shader(const string &path) {
    const auto vertexShader =
        compileShader("assets/shader/" + path + ".vert", GL_VERTEX_SHADER);
    const auto fragmentShader =
        compileShader("assets/shader/" + path + ".frag", GL_FRAGMENT_SHADER);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);

    glLinkProgram(m_program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int success;
    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success) {
        char info[ERROR_LOG_LEN];
        glGetProgramInfoLog(m_program, ERROR_LOG_LEN, nullptr, info);
        throw GameError(string(info));
    }
}

Shader::~Shader() {
    glDeleteProgram(m_program);
}