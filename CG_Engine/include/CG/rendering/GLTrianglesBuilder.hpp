
#include <vector>
#include <memory>

#include "CG/internal/Vertex.hpp"
#include "CG/internal/Texture.hpp"

#include "GLTriangles.hpp"

namespace CG {

struct GLTrianglesBuilder {
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;

	std::shared_ptr<Texture> texture = nullptr; // null if no texture TODO: remove, delegate to material or something

	GLTriangles build() const noexcept;
};

}