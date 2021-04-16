#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include "CG/rendering/GLTriangles.hpp"
#include "CG/internal/Vertex.hpp"
#include "CG/Color.hpp"

namespace CG {

class ShaderProgram;

class SphereRenderer {
public:
	// TODO: static shader

	SphereRenderer(std::uint32_t slices = 50, std::uint32_t stacks = 50) noexcept;

	void draw(const ShaderProgram &sm) const noexcept;

private:
	void generateVertices();
	void _generateVertices(float *, float *, float *, GLuint *);

	void registerVertices(const std::vector<Vertex> &vertices, const std::vector<std::uint32_t> &indices);
private:
	static constexpr float kRadius = 0.5f;

	GLTriangles m_drawable;
	GLuint m_slices, m_stacks;
};

}
