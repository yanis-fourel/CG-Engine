#include <stdexcept>
#include <spdlog/spdlog.h>

#include <assimp/Importer.hpp>        
#include <assimp/scene.h>          
#include <assimp/postprocess.h>    
#include <assimp/matrix4x4.h>    

#include "CG/components/renderer/MeshRenderer.hpp"
#include "CG/internal/ShaderProgram.hpp"
#include "CG/rendering/GLTrianglesBuilder.hpp"

CG::MeshRenderer::MeshRenderer(const std::string &path) : m_fileDir(getDirectoryOfFile(path))
{
	Assimp::Importer importer;

	spdlog::info("Loading asset '{}'", path);
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
		throw std::runtime_error(fmt::format("Could not import asset '{}' : {}", path, importer.GetErrorString()));

	spdlog::info("Processing asset '{}'", path);

	processTextures(scene);
	processAssimpNode(scene, scene->mRootNode, {});
}

void CG::MeshRenderer::draw(const ShaderProgram &sm) const noexcept
{
	for (const auto &d : m_meshesDrawable) {
		d.draw(sm);
	}
}

std::string CG::MeshRenderer::getDirectoryOfFile(const std::string &file) noexcept
{
	std::string directory;
	const size_t last_backslash_idx = file.rfind('\\');
	const size_t last_slash_idx = file.rfind('/');

	size_t idx;

	if (last_backslash_idx != std::string::npos && last_slash_idx != std::string::npos)
		idx = std::max(last_backslash_idx, last_slash_idx);
	else if (last_backslash_idx != std::string::npos)
		idx = last_backslash_idx;
	else
		idx = last_slash_idx;

	if (std::string::npos != idx)
	{
		directory = file.substr(0, idx);
	}

	return directory;
}

void CG::MeshRenderer::processTextures(const aiScene *scene) noexcept
{
	m_textures.reserve(scene->mNumMaterials);

	for (unsigned i = 0; i < scene->mNumMaterials; ++i) {
		aiString path;

		const auto ret = scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &path);

		// note : does not handle embeeded textures
		if (ret != AI_SUCCESS) {
			spdlog::info("'{}' has no texture", scene->mMaterials[i]->GetName().C_Str());
			m_textures.push_back(nullptr);
		}
		else
			m_textures.push_back(std::make_shared<Texture>(m_fileDir + "/" + path.C_Str()));
	}
}

void CG::MeshRenderer::processAssimpNode(const aiScene *scene, const aiNode *node, aiMatrix4x4 parentTransform) noexcept
{
	aiMatrix4x4 transform = node->mTransformation * parentTransform;

	for (unsigned i = 0; i < node->mNumMeshes; ++i) {
		const auto *mesh = scene->mMeshes[node->mMeshes[i]];
		processAssimpMesh(scene, mesh, transform);
	}

	for (unsigned i = 0; i < node->mNumChildren; ++i)
		processAssimpNode(scene, node->mChildren[i], transform);
}

void CG::MeshRenderer::processAssimpMesh(const aiScene *scene, const aiMesh *mesh, aiMatrix4x4 origin) noexcept
{
	GLTrianglesBuilder builder;
	builder.vertices.reserve(mesh->mNumVertices);
	builder.indices.reserve(static_cast<std::size_t>(mesh->mNumFaces) * 3);

	if (mesh->mTextureCoords)
		builder.texture = m_textures[mesh->mMaterialIndex];

	for (unsigned i = 0; i < mesh->mNumVertices; ++i) {
		assert(mesh->mNormals && "Currently requires normals");

		const auto &v = origin * mesh->mVertices[i];
		const auto &n = origin * mesh->mNormals[i];
		CG::Vector2 texCoord(0, 0);
		if (mesh->HasTextureCoords(0)) {
			texCoord.x = mesh->mTextureCoords[0][i].x;
			texCoord.y = mesh->mTextureCoords[0][i].y;
		}
		CG::Color color = CG::Color::White();
		if (mesh->HasVertexColors(0)) {
			color.r = mesh->mColors[0][i].r;
			color.g = mesh->mColors[0][i].g;
			color.b = mesh->mColors[0][i].b;
			color.a = mesh->mColors[0][i].a;
		}

		builder.vertices.push_back(CG::Vertex{
			   CG::Vector3(v.x, v.y, v.z),
			   CG::Vector3(n.x, n.y, n.z),
			   color,
			   texCoord
			});
	}

	for (unsigned i = 0; i < mesh->mNumFaces; ++i) {
		const auto &v = mesh->mFaces[i];

		assert(v.mNumIndices == 3);

		builder.indices.push_back(v.mIndices[0]);
		builder.indices.push_back(v.mIndices[1]);
		builder.indices.push_back(v.mIndices[2]);
	}

	m_meshesDrawable.push_back(builder.build());
}