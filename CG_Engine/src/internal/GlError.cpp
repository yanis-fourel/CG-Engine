#include <iostream>
#include <GL/glew.h>

#include "CG/internal/GlError.hpp"


void CG::GlClearError() noexcept
{
	while (glGetError() != GL_NO_ERROR)
		;
}

bool CG::GLLogCall(const char *function, const char *file, int line) noexcept
{
	bool ret = false;

	while (GLenum err = glGetError() != GL_NO_ERROR) {
		std::cout << "[OpenGl Error " << err << "] '" << function << "' in " << file << ":" << line << "\n\t" << glewGetErrorString(err) << std::endl;
		ret = true;
	}

	return ret;
}
