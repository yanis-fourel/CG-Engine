#pragma once

#include <GL/glew.h>
#include <vector>

namespace CG {

struct Drawable {
	GLuint vbo = -1;
	GLuint vao = -1; // needed ?
	std::vector<unsigned int> indices;
	// Shader ref ? or in renderer

	void draw() const noexcept;
};

}
