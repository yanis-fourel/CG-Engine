#pragma once

#include <string_view>

#include "CG/Color.hpp"
#include "CG/internal/Material.hpp"


namespace CG {

struct MaterialSolid {
	static constexpr std::string_view VertexShaderPath = "solid.vert.glsl";
	static constexpr std::string_view FragmentShaderPath = "solid.frag.glsl";

	void uploadUniforms() const noexcept;


	Color ambiant;
	Color diffuse;
	Color specular;
	float shininess;
	float opacity = 1;

	MaterialSolid &operator=(const MaterialSolid &other)
	{
		ambiant = other.ambiant;
		diffuse = other.diffuse;
		specular = other.specular;
		shininess = other.shininess;
		opacity = other.opacity;

		return *this;
	}


	// taken from http://devernay.free.fr/cours/opengl/materials.html
	static constexpr MaterialSolid Default() { return { {0.8f, 0.8f, 0.8f}, { 0.5f, 0.5f, 0.5f}, {0.01f, 0.01f, 0.01f}, 0.05f * 128 }; }
	static constexpr MaterialSolid Emerald() { return { {0.0215f, 0.1745f, 0.0215f}, { 0.07568f, 0.61424f, 0.07568f}, {0.633f, 0.727811f, 0.633f}, 0.6f * 128 }; }
	static constexpr MaterialSolid Jade() { return { {0.135f, 0.2225f, 0.1575f}, {0.54f, 0.89f, 0.63f}, {0.316228f, 0.316228f, 0.316228f}, 0.1f * 128 }; }
	static constexpr MaterialSolid Obsidian() { return { {0.05375f, 0.05f, 0.06625f}, {0.18275f, 0.17f, 0.22525f}, {0.332741f, 0.328634f, 0.346435f}, 0.3f * 128 }; }
	static constexpr MaterialSolid Pearl() { return { {0.25f, 0.20725f, 0.20725f}, {1, 0.829f, 0.829f}, {0.296648f, 0.296648f, 0.296648f}, 0.088f * 128 }; }
	static constexpr MaterialSolid Ruby() { return { {0.1745f, 0.01175f, 0.01175f}, {0.61424f, 0.04136f, 0.04136f}, {0.727811f, 0.626959f, 0.626959f}, 0.6f * 128 }; }
	static constexpr MaterialSolid Turquoise() { return { {0.1f, 0.18725f, 0.1745f}, {0.396f, 0.74151f, 0.69102f}, {0.297254f, 0.30829f, 0.306678f}, 0.1f * 128 }; }
	static constexpr MaterialSolid Brass() { return { {0.329412f, 0.223529f, 0.027451f}, {0.780392f, 0.568627f, 0.113725f}, {0.992157f, 0.941176f, 0.807843f}, 0.21794872f * 128 }; }
	static constexpr MaterialSolid Bronze() { return { {0.2125f, 0.1275f, 0.054f}, {0.714f, 0.4284f, 0.18144f}, {0.393548f, 0.271906f, 0.166721f}, 0.2f * 128 }; }
	static constexpr MaterialSolid Chrome() { return { {0.25f, 0.25f, 0.25f}, {0.4f, 0.4f, 0.4f}, {0.774597f, 0.774597f, 0.774597f}, 0.6f * 128 }; }
	static constexpr MaterialSolid Copper() { return { {0.19125f, 0.0735f, 0.0225f}, {0.7038f, 0.27048f, 0.0828f}, {0.256777f, 0.137622f, 0.086014f}, 0.1f * 128 }; }
	static constexpr MaterialSolid Gold() { return { {0.24725f, 0.1995f, 0.0745f}, {0.75164f, 0.60648f, 0.22648f}, {0.628281f, 0.555802f, 0.366065f}, 0.4f * 128 }; }
	static constexpr MaterialSolid Silver() { return { {0.19225f, 0.19225f, 0.19225f}, {0.50754f, 0.50754f, 0.50754f}, {0.508273f, 0.508273f, 0.508273f}, 0.4f * 128 }; }

	// Made ambiant effect higher vvv
	static constexpr MaterialSolid BlackPlastic() { return { {0.0f, 0.0f, 0.0f}, {0.01f, 0.01f, 0.01f}, {0.50f, 0.50f, 0.50f}, 0.25f * 128 }; }
	static constexpr MaterialSolid WhitePlastic() { return { {0.25f, 0.25f, 0.25f}, {0.55f, 0.55f, 0.55f}, {0.70f, 0.70f, 0.70f}, 0.25f * 128 }; }
	static constexpr MaterialSolid CyanPlastic() { return { {0.0f, 0.3f, 0.28f}, {0.0f, 0.50980392f, 0.50980392f}, {0.50196078f, 0.50196078f, 0.50196078f}, 0.25f * 128 }; }
	static constexpr MaterialSolid GreenPlastic() { return { {0.025f, 0.1f, 0.025f}, {0.1f, 0.35f, 0.1f}, {0.45f, 0.55f, 0.45f}, 0.25f * 128 }; }
	static constexpr MaterialSolid RedPlastic() { return { {0.25f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.0f}, {0.7f, 0.6f, 0.6f}, 0.25f * 128 }; }
	static constexpr MaterialSolid YellowPlastic() { return { {0.25f, 0.25f, 0.0f}, {0.5f, 0.5f, 0.0f}, {0.60f, 0.60f, 0.50f}, 0.25f * 128 }; }
	static constexpr MaterialSolid BluePlastic() { return { {0.0f, 0.0f, 0.25f}, {0.0f, 0.0f, 0.5f}, {0.6f, 0.6f, 0.7f}, 0.25f * 128 }; }

	static constexpr MaterialSolid BlackRubber() { return { {0.02f, 0.02f, 0.02f}, {0.01f, 0.01f, 0.01f}, {0.4f, 0.4f, 0.4f}, 0.078125f * 128 }; }
	static constexpr MaterialSolid CyanRubber() { return { {0.2f, 0.3f, 0.3f}, {0.4f, 0.5f, 0.5f}, {0.04f, 0.7f, 0.7f}, 0.078125f * 128 }; }
	static constexpr MaterialSolid GreenRubber() { return { {0.2f, 0.3f, 0.2f}, {0.4f, 0.5f, 0.4f}, {0.04f, 0.7f, 0.04f}, 0.078125f * 128 }; }
	static constexpr MaterialSolid RedRubber() { return { {0.3f, 0.2f, 0.2f}, {0.5f, 0.4f, 0.4f}, {0.7f, 0.04f, 0.04f}, 0.078125f * 128 }; }
	static constexpr MaterialSolid WhiteRubber() { return { {0.3f, 0.3f, 0.3f}, {0.5f, 0.5f, 0.5f}, {0.7f, 0.7f, 0.7f}, 0.078125f * 128 }; }
	static constexpr MaterialSolid YellowRubber() { return { {0.3f, 0.3f, 0.2f}, {0.5f, 0.5f, 0.4f}, {0.7f, 0.7f, 0.04f}, 0.078125f * 128 }; }
	static constexpr MaterialSolid BlueRubber() { return { {0.2f, 0.2f, 0.3f}, {0.4f, 0.4f, 0.5f}, {0.04f, 0.04f, 0.7f}, 0.078125f * 128 }; }

};
}