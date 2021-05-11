#include <spdlog/spdlog.h>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "CG/rendering/Texture.hpp"

CG::Texture::Texture(const std::string &path)
{
	data = ::stbi_load(path.c_str(), &width, &height, &nbrChannels, 0); 

	if (!data)
		throw std::runtime_error(std::string("Could not load texture from '") + path + "'");

	spdlog::info("Loaded texture '{}', number of channels : '{}'", path, nbrChannels);
}

CG::Texture::~Texture()
{
	::stbi_image_free(data);
}
