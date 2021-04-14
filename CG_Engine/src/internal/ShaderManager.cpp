#include <fstream>
#include <spdlog/spdlog.h>
#include <glm/gtc/type_ptr.hpp>

#include "CG/internal/ShaderProgram.hpp"
#include "CG/internal/GlError.hpp"

CG::ShaderProgram::~ShaderProgram()
{
	if (_validated)
		GLCall(glDeleteProgram(_program));
	for (const auto &s : _shaders)
		GLCall(glDeleteShader(s));
}

void CG::ShaderProgram::addShader(GLenum type, const std::string_view relpath)
{
	std::ifstream ifs(std::string(CG_SHADER_DIR) + relpath.data());

	if (!ifs)
		throw std::runtime_error(std::string("Could not open shader ") + relpath.data());

	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

	if (_validated)
		throw std::logic_error("Program already validated");

	const char *cstr_content = content.data();

	auto shader = glCreateShader(type);

	GLCall(glShaderSource(shader, 1, &cstr_content, nullptr));
	GLCall(glCompileShader(shader));

	int status;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));

	if (status == GL_FALSE) {
		char log[512];
		GLCall(glGetShaderInfoLog(shader, 512, nullptr, log));
		spdlog::error("Error compiling shader '{}' : {}", relpath.data(), log);
	}
	else {
		spdlog::info("Successfully compiled shader '{}'", relpath.data());
		_shaders.push_back(shader);
	}
}

void CG::ShaderProgram::validate()
{
	_validated = true;

	_program = glCreateProgram();

	for (const auto &s : _shaders)
		GLCall(glAttachShader(_program, s));
	GLCall(glLinkProgram(_program));
	GLCall(glValidateProgram(_program));

	GLCall(glUseProgram(_program));

	spdlog::info("Successfully validated shader");
}

void CG::ShaderProgram::use() const noexcept
{
	GLCall(glUseProgram(_program));
}

std::optional<GLint> CG::ShaderProgram::getUniformLocation(std::string_view name) const noexcept
{
	auto position = glGetUniformLocation(_program, name.data());

	if (position != -1)
		return position;
	else {
		// Commented because it was causing lags during Lightning and Material rework
		//spdlog::error("Unknown uniform name '{}'", name.data());
		return {};
	}
}

void CG::ShaderProgram::uploadUniformMat4(std::string_view name, const glm::mat4 &mat) const noexcept
{
	auto position = getUniformLocation(name);

	if (position)
		GLCall(glUniformMatrix4fv(position.value(), 1, GL_FALSE, glm::value_ptr(mat)));
}


void CG::ShaderProgram::uploadUniformMat3(std::string_view name, const glm::mat3 &mat) const noexcept
{
	auto position = getUniformLocation(name);

	if (position)
		GLCall(glUniformMatrix3fv(position.value(), 1, GL_FALSE, glm::value_ptr(mat)));
}

void CG::ShaderProgram::uploadUniformVec4(std::string_view name, const glm::vec4 &vec) const noexcept
{
	auto position = getUniformLocation(name);

	if (position)
		GLCall(glUniform4f(position.value(), vec.x, vec.y, vec.z, vec.w));
}

void CG::ShaderProgram::uploadUniformVec3(std::string_view name, const glm::vec3 &vec) const noexcept
{
	auto position = getUniformLocation(name);

	if (position)
		GLCall(glUniform3f(position.value(), vec.x, vec.y, vec.z));
}

void CG::ShaderProgram::uploadUniform1f(std::string_view name, float f) const noexcept
{
	auto position = getUniformLocation(name);

	if (position)
		GLCall(glUniform1f(position.value(), f));
}

void CG::ShaderProgram::uploadUniform1b(std::string_view name, bool b) const noexcept
{
	auto position = getUniformLocation(name);

	if (position)
		GLCall(glUniform1i(position.value(), b ? GL_TRUE : GL_FALSE));
}
