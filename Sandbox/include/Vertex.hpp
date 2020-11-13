#pragma once

#include <GL/glew.h>

struct Position
{
	static constexpr GLint kValueCount = 3;

	float x;
	float y;
	float z;
};

struct Color
{
	static constexpr GLint kValueCount = 4;

	float r;
	float g;
	float b;
	float a;
};

struct SimpleVertex
{
	Position pos;
	Color col;
};
