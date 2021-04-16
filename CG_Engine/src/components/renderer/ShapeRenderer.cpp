#include "CG/components/renderer/ShapeRenderer.hpp"
#include "CG/rendering/materials/MaterialSolid.hpp"

CG::ShapeRenderer::ShapeRenderer(GLTriangles && triangles)
	: triangles(std::move(triangles)), material(std::make_unique<CG::material::Solid>(CG::material::Solid::Default()))
{}

CG::ShapeRenderer::ShapeRenderer(GLTriangles && triangles, std::unique_ptr<AMaterial>&& material)
	: triangles(std::move(triangles)), material(std::move(material))
{
	if (material == nullptr)
		material = std::make_unique<CG::material::Solid>(CG::material::Solid::Default());
}
