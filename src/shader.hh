#pragma once

#include <GL/glew.h>
#include <string>

#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using std::string;

template <typename T> struct UniformTraits;

#define TEMPLATE_MAP_TYPES_CUSTOM_ARGS(type, gltype, ...)                      \
    template <> struct UniformTraits<type> {                                   \
        static void Apply(const GLint location, const type data) {             \
            glUniform##gltype(location, __VA_ARGS__);                          \
        }                                                                      \
    };

#define TEMPLATE_MAP_TYPES(type, gltype)                                       \
    TEMPLATE_MAP_TYPES_CUSTOM_ARGS(type, gltype, data)
#define TEMPLATE_MAP_TYPESXY(type, gltype)                                     \
    TEMPLATE_MAP_TYPES_CUSTOM_ARGS(type, gltype, data.x, data.y)
#define TEMPLATE_MAP_TYPESXYZ(type, gltype)                                    \
    TEMPLATE_MAP_TYPES_CUSTOM_ARGS(type, gltype, data.x, data.y, data.z)

TEMPLATE_MAP_TYPES(float, 1f)
TEMPLATE_MAP_TYPES(int, 1i)
TEMPLATE_MAP_TYPES(double, 1d)
TEMPLATE_MAP_TYPESXY(glm::vec2, 2f)
TEMPLATE_MAP_TYPESXY(glm::ivec2, 2i)
TEMPLATE_MAP_TYPESXY(glm::dvec2, 2d)
TEMPLATE_MAP_TYPESXYZ(glm::vec3, 3f)
TEMPLATE_MAP_TYPESXYZ(glm::ivec3, 3i)
TEMPLATE_MAP_TYPESXYZ(glm::dvec3, 3d)

#undef TEMPLATE_MAP_TYPES
#undef TEMPLATE_MAP_TYPESXY
#undef TEMPLATE_MAP_TYPESXYZ
#undef TEMPLATE_MAP_TYPES_CUSTOM_ARGS

class Shader {
    GLuint m_program;
    static GLuint compileShader(const string &path, GLenum type);

  public:
    void use() const;
    explicit Shader(const string &path);
    ~Shader();

    template <typename T> void uniform(const string &name, T type) {
        use();
        const auto location = glGetUniformLocation(m_program, name.c_str());
        UniformTraits<T>::Apply(location, type);
    }
};