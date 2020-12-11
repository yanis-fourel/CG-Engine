#include <stdexcept>
#include <spdlog/spdlog.h>

#include <assimp/Importer.hpp>        
#include <assimp/scene.h>          
#include <assimp/postprocess.h>    
#include <assimp/matrix4x4.h>    

#include "CG/components/renderer/MeshRenderer.hpp"


CG::MeshRenderer::MeshRenderer(const std::string &path)
{
	Assimp::Importer importer;

	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate);

	if (!scene)
		throw std::runtime_error(fmt::format("Could not import asset '{}' : {}", path, importer.GetErrorString()));
	else
		spdlog::trace("Loading mesh '{}'", path);

	processAssimpNode(scene, scene->mRootNode, {});
}

void CG::MeshRenderer::draw() const noexcept
{
	for (const auto &d : m_meshesDrawable)
		d.draw();
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

	for (unsigned i = 0; i < mesh->mNumVertices; ++i) {
		assert(mesh->mNormals && "Currently needs normals");

		const auto &v = origin * mesh->mVertices[i];
		const auto &n = origin * mesh->mNormals[i];

		builder.vertices.push_back(CG::Vertex{
			   CG::Vector3(v.x, v.y, v.z),
			   CG::Vector3(n.x, n.y, n.z),
			   CG::Color::White() // TODO: color ?
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