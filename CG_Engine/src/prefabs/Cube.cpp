#include "CG/prefabs/Cube.hpp"
#include "CG/components/Transform.hpp"
#include "CG/components/renderer/ShapeRenderer.hpp"

CG::prefabs::Cube::Cube(const CG::Transform &transform)
{
	addComponent<CG::Transform>(transform);
	addComponent<CG::ShapeRenderer>(CG::ShapeRenderer::Cube());
}
