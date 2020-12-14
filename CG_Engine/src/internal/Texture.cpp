#include <spdlog/spdlog.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "CG/internal/Texture.hpp"

CG::Texture::Texture(const std::string &path)
{
	data = ::stbi_load(path.c_str(), &width, &height, &nbrChannels, 0); 

	spdlog::info("Loaded texture '{}', number of channels : '{}'", path, nbrChannels);
}

CG::Texture::~Texture()
{
	::stbi_image_free(data);
}
