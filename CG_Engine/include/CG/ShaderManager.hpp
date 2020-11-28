#pragma once

#include <vector>
#include <string>
#include <string_view>
#include <optional>

#include <GL/glew.h>
#include <glm/glm.hpp>

namespace CG {

class ShaderManager
{
public:
    ~ShaderManager();
    void addShader(GLenum type, const std::string_view content);
    void validate();
    
    void use();

    // TODO: template
    void uploadUniformMat4(std::string_view name, const glm::mat4 &mat);
    void uploadUniformMat3(std::string_view name, const glm::mat3 &mat);

private:
    std::optional<GLint> getUniformLocation(std::string_view name) const noexcept;

private:
    static const char *kShaderDir;

    bool _validated = false;
    std::vector<GLuint> _shaders;
    GLuint _program = -1;
};

}
