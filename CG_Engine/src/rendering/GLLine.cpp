#include <optional>

#include "CG/rendering/GLLine.hpp"
#include "CG/internal/GlError.hpp"

GLuint CG::GLLine::getVao() noexcept
{
	static std::optional<GLuint> static_vao = {};

	if (static_vao) [[likely]]
		return static_vao.value();


    float vertices[2] = {0.f, 1.f};

    GLuint vao;
    GLuint vbo;

	glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    static_vao = vao;
    return vao;
}
