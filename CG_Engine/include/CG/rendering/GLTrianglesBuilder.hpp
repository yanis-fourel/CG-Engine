
#include <vector>
#include <memory>

#include "CG/internal/Vertex.hpp"
#include "CG/rendering/Texture.hpp"

#include "GLTriangles.hpp"

namespace CG {

struct GLTrianglesBuilder {
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;

	GLTriangles build() const noexcept;
};

}