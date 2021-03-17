#pragma once

#if 1
#define DEBUG_BREAK_ON_GL_ERR __debugbreak()
#else
#define DEBUG_BREAK_ON_GL_ERR {}
#endif

#define GLCall(x) \
	do {												\
		::CG::GlClearError();							\
		x;												\
		if(::CG::GLLogCall(#x, __FILE__, __LINE__))		\
			DEBUG_BREAK_ON_GL_ERR;						\
	} while (0);

namespace CG {

void GlClearError() noexcept;
bool GLLogCall(const char *function, const char *file, int line) noexcept;

}
