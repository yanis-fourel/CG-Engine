#pragma once

#include <string>

// TODO: resource cache

namespace CG {

struct Texture {
	Texture(const std::string &path);
	~Texture();

	// delete because of problem with ownership of `data`
	Texture(const Texture &) = delete;
	Texture &operator=(const Texture &) = delete;

	int width;
	int height;
	unsigned char *data;
};

}