
#include <vector>
#include <memory>

#include "CG/internal/Vertex.hpp"
#include "CG/internal/Texture.hpp"
#include "Drawable.hpp"

namespace CG {

struct DrawableBuilder {
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;

	std::unique_ptr<Texture> texture; // null if no texture

	Drawable build() const noexcept;
};

}