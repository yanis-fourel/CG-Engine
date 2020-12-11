#pragma once

#include <string>

#include "CG/internal/DrawableBuilder.hpp"

struct aiScene;
struct aiNode;
struct aiMesh;

// very questionnable way of foward declaring it
template <typename T> class aiMatrix4x4t;
using ai_real = float;
typedef aiMatrix4x4t<ai_real> aiMatrix4x4;

namespace CG {

class MeshRenderer {
public:
	// TODO: static shader

	MeshRenderer(const std::string &path);

	void draw() const noexcept;

private:
	void processAssimpNode(const aiScene *scene, const aiNode *node, aiMatrix4x4 parentTransform) noexcept;
	void processAssimpMesh(const aiScene *scene, const aiMesh *mesh, aiMatrix4x4 origin) noexcept;

private:
	std::vector<Drawable> m_meshesDrawable;
};

}
