#pragma once

#include "CG/Color.hpp"
#include "CG/rendering/Material.hpp"
#include "CG/rendering/ShaderProgram.hpp"

namespace CG::material {

struct Checkerboard : public AMaterial {
	static constexpr std::string_view VertexShaderPath = "checkerboard.vert.glsl";
	static constexpr std::string_view FragmentShaderPath = "checkerboard.frag.glsl";

public:
	Color color1, color2;

	CG::Vector3 size;

	float shininess = 16;
	float ambiantFactor = 1.0;
	float diffuseFactor = 0.5;
	float specularFactor = 0.2;
public:
	Checkerboard() = default;
	constexpr Checkerboard(Color c1, Color c2, CG::Vector3 size = CG::Vector3::One()) noexcept
		: color1(c1), color2(c2), size(size)
	{}

	void uploadUniforms() const noexcept override;
	bool hasTransparence() const noexcept override { return false; }
	auto getShader() const noexcept -> const ShaderProgram & override { return getMaterialShader<Checkerboard>(); }
};
}