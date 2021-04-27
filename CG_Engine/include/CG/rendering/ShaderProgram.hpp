#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <optional>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace CG {

class ShaderProgram
{
public:
    ~ShaderProgram();
    void addShader(GLenum type, const std::string_view relpath);
    void validate();
    
    void use() const noexcept;

    // TODO: template overloaded
    void uploadUniformMat4(std::string_view name, const glm::mat4 &mat) const noexcept;
    void uploadUniformMat3(std::string_view name, const glm::mat3 &mat) const noexcept;
    void uploadUniformVec4(std::string_view name, const glm::vec4 &vec) const noexcept;
    void uploadUniformVec3(std::string_view name, const glm::vec3 &vec) const noexcept;
    void uploadUniform1f(std::string_view name, float f) const noexcept;
    void uploadUniform1b(std::string_view name, bool b) const noexcept;

private:
    std::optional<GLint> getUniformLocation(std::string_view name) const noexcept;

private:
    static const char *kShaderDir;

    bool _validated = false;
    std::vector<GLuint> _shaders;
    GLuint _program = -1;

#ifndef NDEBUG
    std::string m_debugName = "";
#endif
};

}
