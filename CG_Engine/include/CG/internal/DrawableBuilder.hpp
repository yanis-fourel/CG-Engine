
#include <vector>
#include <memory>

#include "CG/internal/Vertex.hpp"
#include "CG/internal/Texture.hpp"
#include "Drawable.hpp"

namespace CG {

struct DrawableBuilder {
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;

	std::shared_ptr<Texture> texture = nullptr; // null if no texture

	Drawable build() const noexcept;
};

}