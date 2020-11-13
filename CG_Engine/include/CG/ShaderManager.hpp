/*
** EPITECH PROJECT, 2019
** Project
** File description:
** ShaderManager.hpp
*/

#pragma once

#include <vector>
#include <string>
#include <string_view>

#include <GL/glew.h>
#include <glm/glm.hpp>

class ShaderManager
{
public:
    ~ShaderManager();
    void addShader(GLenum type, const std::string_view content);
    void validate();
    
    void use();
    void uploadUniformMat4(const std::string &name, const glm::mat4 &mat);
private:
    static const char *kShaderDir;

    bool _validated = false;
    std::vector<GLuint> _shaders;
    GLuint _program = -1;
};
