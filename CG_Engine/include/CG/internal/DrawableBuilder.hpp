
#include <vector>

#include "CG/internal/Vertex.hpp"
#include "Drawable.hpp"

namespace CG {

struct DrawableBuilder {
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;

	Drawable build() const noexcept;
};

}