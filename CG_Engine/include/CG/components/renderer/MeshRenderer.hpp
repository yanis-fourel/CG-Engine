#pragma once

#include <string>

#include "CG/internal/DrawableBuilder.hpp"

struct aiScene;
struct aiNode;

namespace CG {

class MeshRenderer {
public:
	// TODO: static shader

	MeshRenderer(const std::string &path);

	inline void draw() const noexcept { m_drawable.draw(); }

private:
	DrawableBuilder processAssimpScene(const aiScene *scene);

private:
	Drawable m_drawable;
};

}
