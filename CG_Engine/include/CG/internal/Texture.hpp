#pragma once

#include <string>

namespace CG {

struct Texture {
	Texture(const std::string &path);
	~Texture();

	// problem with ownership of `data`
	Texture(const Texture &) = delete;
	Texture &operator=(const Texture &) = delete;

	int width;
	int height;
	int nbrChannels; // what is that ?
	unsigned char *data;
};

}