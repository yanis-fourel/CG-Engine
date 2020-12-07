#include <fstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "CG/internal/ShaderManager.hpp"

CG::ShaderManager::~ShaderManager()
{
	if (_validated)
		glDeleteProgram(_program);
	for (const auto &s : _shaders)
		glDeleteShader(s);
}

void CG::ShaderManager::addShader(GLenum type, const std::string_view relpath)
{
	std::ifstream ifs(std::string(CG_SHADER_DIR) + relpath.data());

	if (!ifs)
		throw std::runtime_error(std::string("Could not open shader ") + relpath.data());

	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

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
		std::cerr << "Error compiling shader '" << relpath << "' : " << log << std::endl;
	}
	else
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

std::optional<GLint> CG::ShaderManager::getUniformLocation(std::string_view name) const noexcept
{
	auto position = glGetUniformLocation(_program, name.data());

	if (position != -1)
		return position;
	else {
		std::cerr << "Unknown uniform name '" << name << "'" << std::endl;
		return {};
	}
}

void CG::ShaderManager::uploadUniformMat4(std::string_view name, const glm::mat4 &mat)
{
	auto position = getUniformLocation(name);

	if (position)
		glUniformMatrix4fv(position.value(), 1, GL_FALSE, glm::value_ptr(mat));
}


void CG::ShaderManager::uploadUniformMat3(std::string_view name, const glm::mat3 &mat)
{
	auto position = getUniformLocation(name);

	if (position)
		glUniformMatrix3fv(position.value(), 1, GL_FALSE, glm::value_ptr(mat));
}

void CG::ShaderManager::uploadUniformVec4(std::string_view name, const glm::vec4 &vec)
{
	auto position = getUniformLocation(name);

	if (position)
		glUniform4f(position.value(), vec.x, vec.y, vec.z, vec.w);
}

void CG::ShaderManager::uploadUniformVec3(std::string_view name, const glm::vec3 &vec)
{
	auto position = getUniformLocation(name);

	if (position)
		glUniform3f(position.value(), vec.x, vec.y, vec.z);
}

void CG::ShaderManager::uploadUniform1f(std::string_view name, float f)
{
	auto position = getUniformLocation(name);

	if (position)
		glUniform1f(position.value(), f);
}