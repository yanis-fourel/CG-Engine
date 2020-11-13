#pragma once


#include <glm/vec3.hpp>
#include <GL/glew.h>

#include "CG/Camera.hpp"

class Cube
{
public:
	Cube(glm::vec3 pos, glm::vec3 size);

	void draw();

private:
	GLuint _vbo;
	GLuint _vao;
};
