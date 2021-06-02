#include "CG/prefabs/Cube.hpp"
#include "CG/components/renderer/ShapeRenderer.hpp"
#include "CG/components/Transform.hpp"

CG::prefabs::Cube::Cube()
{
	addComponent<CG::Transform>();
	addComponent<CG::ShapeRenderer>(CG::ShapeRenderer::Cube());
}
