#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

#include "CG/Material.hpp"
#include "CG/internal/Drawable.hpp"
#include "CG/internal/Vertex.hpp"
#include "CG/Color.hpp"

namespace CG {

class ShaderManager;

class SphereRenderer {
public:
	// TODO: static shader

	SphereRenderer(const Color &color, std::uint32_t slices = 50, std::uint32_t stacks = 50) noexcept;

	void draw(ShaderManager &sm) const noexcept;

	[[nodiscard]] auto getMaterial() const noexcept -> const Material &{ return m_drawable.material; }
	void setMaterial(const Material &mat) noexcept { m_drawable.material = mat; }

private:
	void generateVertices(const Color &color);
	void _generateVertices(float *, float *, float *, GLuint *);

	void registerVertices(const std::vector<Vertex> &vertices, const std::vector<std::uint32_t> &indices);
private:
	static constexpr float kRadius = 1.0f;

	Drawable m_drawable;
	GLuint m_slices, m_stacks;
};

}
