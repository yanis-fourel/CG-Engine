#pragma once

#include <string>
#include <unordered_map>
#include <memory>

#include "CG/internal/DrawableBuilder.hpp"

struct aiScene;
struct aiNode;
struct aiMesh;

// very questionnable way of foward declaring it
template <typename T> class aiMatrix4x4t;
using ai_real = float;
typedef aiMatrix4x4t<ai_real> aiMatrix4x4;

namespace CG {

class ShaderProgram;

class MeshRenderer {
public:
	MeshRenderer(const std::string &path);

	void draw(ShaderProgram &sm) const noexcept;

private:
	static std::string getDirectoryOfFile(const std::string &file) noexcept;
	void processTextures(const aiScene *scene) noexcept;
	void processAssimpNode(const aiScene *scene, const aiNode *node, aiMatrix4x4 parentTransform) noexcept;
	void processAssimpMesh(const aiScene *scene, const aiMesh *mesh, aiMatrix4x4 origin) noexcept;

private:
	std::string m_fileDir;
	std::vector<std::shared_ptr<Texture>> m_textures;
	std::vector<Drawable> m_meshesDrawable;
};

}
