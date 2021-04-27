#pragma once

#include "CG/Color.hpp"
#include "CG/rendering/Material.hpp"
#include "CG/rendering/ShaderProgram.hpp"

namespace CG::material {

struct Line : public AMaterial {
	static constexpr std::string_view VertexShaderPath = "simpleLine.vert.glsl";
	static constexpr std::string_view FragmentShaderPath = "simpleLine.frag.glsl";

public:
	Color color;


public:
	Line() = default;
	constexpr Line(Color color) noexcept : color(color)
	{}

	void uploadUniforms() const noexcept override;
	bool hasTransparence() const noexcept override { return false; }
	auto getShader() const noexcept -> const ShaderProgram & override { return getMaterialShader<Line>(); }
};
}