#include <stdexcept>
#include <spdlog/spdlog.h>

#include <assimp/Importer.hpp>        
#include <assimp/scene.h>          
#include <assimp/postprocess.h>    
#include <assimp/matrix4x4.h>    

#include "CG/components/renderer/MeshRenderer.hpp"
#include "CG/internal/ShaderManager.hpp"

CG::MeshRenderer::MeshRenderer(const std::string &path) : m_fileDir(getDirectoryOfFile(path))
{
	Assimp::Importer importer;

	spdlog::info("Loading asset '{}'", path);
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
		throw std::runtime_error(fmt::format("Could not import asset '{}' : {}", path, importer.GetErrorString()));

	spdlog::info("Processing asset '{}'", path);

	processAssimpNode(scene, scene->mRootNode, {});
}

void CG::MeshRenderer::draw(ShaderManager &sm) const noexcept
{
	for (const auto &d : m_meshesDrawable) {
		sm.uploadUniform1b("u_hasTexture", d.hasTexture);
		d.draw();
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
	DrawableBuilder builder;
	builder.vertices.reserve(mesh->mNumVertices);
	builder.indices.reserve(static_cast<std::size_t>(mesh->mNumFaces) * 3);

	//mesh->mMaterialIndex;
	//mesh->mTextureCoords[0]->x ; mesh->mTextureCoords[0]->y ; 
	//scene->mTextures[0]->pcData

	if (mesh->mTextureCoords) {
		aiString path;

		const auto ret = scene->mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &path);

		// note : does not handle embeeded textures
		if (ret != AI_SUCCESS)
			spdlog::error("Failed to query aiTextureType_DIFFUSE on '{}'", mesh->mName.C_Str());
		else
			builder.texture = std::make_unique<Texture>(m_fileDir + "/" + path.C_Str());
	}

	for (unsigned i = 0; i < mesh->mNumVertices; ++i) {
		assert(mesh->mNormals && "Currently requires normals");

		const auto &v = origin * mesh->mVertices[i];
		const auto &n = origin * mesh->mNormals[i];
		CG::Vector2 texCoord;
		if (mesh->HasTextureCoords(0)) {
			texCoord.x = mesh->mTextureCoords[0][i].x;
			texCoord.y = mesh->mTextureCoords[0][i].y;
		}

		builder.vertices.push_back(CG::Vertex{
			   CG::Vector3(v.x, v.y, v.z),
			   CG::Vector3(n.x, n.y, n.z),
			   CG::Color::White(), // TODO: color ?
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