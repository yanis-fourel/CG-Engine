#include <spdlog/spdlog.h>
#include <GL/glew.h>

#include "CG/internal/GlError.hpp"


void CG::GlClearError() noexcept
{
	while (glGetError() != GL_NO_ERROR)
		;
}

bool CG::GLLogCall(const char *call, const char *file, int line) noexcept
{
	bool ret = false;

	while (GLenum err = glGetError()) {
		auto errString = gluErrorString(err);

		if (errString)
			spdlog::error("[OpenGl Error {}] '{}' in {}:{}\n\t{}", err, call, file, line, errString);
		else
			spdlog::error("[OpenGl Error {}] '{}' in {}:{}\n\tUnknown", err, call, file, line);

		ret = true;
	}

	return ret;
}
