#pragma once

#include <memory>

#include "CG/internal/ShaderProgram.hpp"

namespace CG {

template <typename T>
concept Material = requires(T a)
{
	T::VertexShaderPath;
	T::FragmentShaderPath;

	{ a.uploadUniforms()} noexcept;
};

template <Material T>
const ShaderProgram &getMaterialShader()
{
	static ShaderProgram *shaderProgram;

	if (!shaderProgram) {
		shaderProgram = new ShaderProgram(); // TODO: fix never destroys the program. 

		shaderProgram->addShader(GL_VERTEX_SHADER, T::VertexShaderPath);
		shaderProgram->addShader(GL_FRAGMENT_SHADER, T::FragmentShaderPath);
		shaderProgram->validate();
	}

	return *shaderProgram;
}

}
