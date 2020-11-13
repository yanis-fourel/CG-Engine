#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "CG/ShaderManager.hpp"

CG::ShaderManager::~ShaderManager()
{
    if (_validated)
        glDeleteProgram(_program);
    for (const auto &s : _shaders)
        glDeleteShader(s);
}

void CG::ShaderManager::addShader(GLenum type, const std::string_view content)
{
    if (_validated)
        throw std::logic_error("Program already validated");

    const char *cstr_content = content.data();

    auto shader = glCreateShader(type);

    glShaderSource(shader, 1, &cstr_content, nullptr);
    glCompileShader(shader);

    int status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Error compiling shader '" << content << "' : " << log << std::endl;
    } else
        _shaders.push_back(shader);
}

void CG::ShaderManager::validate()
{
    _validated = true;

    _program = glCreateProgram();

    for (const auto &s : _shaders)
        glAttachShader(_program, s);
    glLinkProgram(_program);
    glValidateProgram(_program);

    glUseProgram(_program);
}

void CG::ShaderManager::use()
{
    glUseProgram(_program);
}

void CG::ShaderManager::uploadUniformMat4(const std::string& name, const glm::mat4& mat)
{
    auto position = glGetUniformLocation(_program, name.c_str());

    if (position != -1)
        glUniformMatrix4fv(position, 1, GL_FALSE, glm::value_ptr(mat));
    else
        std::cerr << "Unknown uniform name '" << name << "'" << std::endl;
}
