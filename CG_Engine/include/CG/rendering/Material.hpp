#pragma once

#include <memory>

#include "CG/rendering/ShaderProgram.hpp"

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

class AMaterial
{
public:
	virtual ~AMaterial() = default;

public:
	virtual void uploadUniforms() const noexcept = 0;
	virtual bool hasTransparence() const noexcept = 0; // TODO: (opti) store separately in ECS
	virtual auto getShader() const noexcept -> const ShaderProgram & = 0;
};

}
