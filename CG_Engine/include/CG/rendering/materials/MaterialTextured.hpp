#pragma once

#include <string_view>

#include "CG/Color.hpp"
#include "CG/rendering/Material.hpp"

namespace CG::material {

struct Textured : public AMaterial {
	static constexpr std::string_view VertexShaderPath = "textured.vert.glsl";
	static constexpr std::string_view FragmentShaderPath = "textured.frag.glsl";

	Textured() = default;
	Textured(std::string_view texturePath,
		Color ambiant =  {0.8f, 0.8f, 0.8f},
		Color diffuse = { 0.5f, 0.5f, 0.5f},
		Color specular = {0.01f, 0.01f, 0.01f},
		float shininess = 0.05f * 128,
		float opacity = 1) noexcept
		: ambiant(ambiant), diffuse(diffuse), specular(specular), shininess(shininess), opacity(opacity)
	{
		setTexture(texturePath);
	}

	void uploadUniforms() const noexcept override;
	bool hasTransparence() const noexcept override { return opacity < 1; }
	auto getShader() const noexcept -> const ShaderProgram & override { return getMaterialShader<Textured>(); }

	Color ambiant;
	Color diffuse;
	Color specular;
	float shininess;
	float opacity = 1;

	// TODO: replace with simplified : (and later option for diffuseMap, specularMaps etc...)
	//	float shininess = 16;
	//float ambiantFactor = 1.0;
	//float diffuseFactor = 0.5;
	//float specularFactor = 0.2;


private:
	GLuint textureID; // TODO: move texture to different material?
	bool has_texture = false;
public:
	void setTexture(std::string_view path);

	// TODO:  find a way to remove that (or =default)
	Textured &operator=(const Textured &other)
	{
		ambiant = other.ambiant;
		diffuse = other.diffuse;
		specular = other.specular;
		shininess = other.shininess;
		opacity = other.opacity;
		textureID = other.textureID;
		has_texture = other.has_texture;
		return *this;
	}


};
}