#pragma once

#include <memory>
#include <cassert>

#include "CG/rendering/GLTriangles.hpp"
#include "CG/rendering/Material.hpp"

namespace CG {


struct ShapeRenderer 
{
	GLTriangles triangles;
	std::unique_ptr<AMaterial> material; // note: having a pointer here prevent from using cache optimisation. bad

	explicit ShapeRenderer(GLTriangles &&triangles);
	explicit ShapeRenderer(GLTriangles &&triangles, std::unique_ptr<AMaterial> &&material);

	static ShapeRenderer Cube();
	static ShapeRenderer Plane();
	static ShapeRenderer Sphere(std::uint32_t slices = 50, std::uint32_t stacks = 50);


	inline void draw() const noexcept
	{
		assert(material && "User __has to__ provide a material");

		material->uploadUniforms();
		triangles.draw(material->getShader());
	}

	inline bool hasTransparence() const noexcept { assert(material && "User __has to__ provide a material"); return material->hasTransparence(); }
};

}
