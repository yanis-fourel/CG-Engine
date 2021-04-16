#pragma once

#include <GL/glew.h>

namespace CG {

struct GLLine {

	static inline void draw() noexcept
	{
		glBindVertexArray(getVao());

		glDrawArrays(GL_LINES, 0, 2);
	}

private:
	static GLuint getVao() noexcept;
};

}
