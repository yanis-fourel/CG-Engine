#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include "CG/internal/Drawable.hpp"
#include "CG/internal/Vertex.hpp"
#include "CG/Color.hpp"

namespace CG {

class SphereRenderer {
public:
	// TODO: static shader

	SphereRenderer(const Color &color, std::uint32_t slices = 50, std::uint32_t stacks = 50) noexcept;

	inline void draw() const noexcept { m_drawable.draw(); }

private:
	void generateVertices(const Color &color);
	void _generateVertices(float *, float *, float *, GLuint *);

	void registerVertices(const std::vector<Vertex> &vertices, const std::vector<std::uint32_t> &indices);
private:
	static constexpr float kRadius = 0.5f; // Real diameter will be the scale of the sphere

	Drawable m_drawable;
	GLuint m_slices, m_stacks;
};

}
