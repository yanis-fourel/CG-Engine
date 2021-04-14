#include <entt/entt.hpp>

#include "CG/rendering/RenderSystem.hpp"

#include "CG/components/PointLight.hpp"
#include "CG/components/Transform.hpp"

#include "CG/components/renderer/_all.hpp"

#include "CG/rendering/RendererHelper.hpp"

void CG::Renderer::renderScene(ShaderManager &onlyshader, const AGame &game) noexcept
{
	// TODO: multiple shader management
	onlyshader.use();

	onlyshader.uploadUniformMat4("u_viewProj", game.getCamera().getViewProjMatrix());
	onlyshader.uploadUniformVec3("u_ambiantLightColor", game.getAmbiantLight().toVec3());
	onlyshader.uploadUniformVec3("u_eyePos", game.getCamera().getPosition());


	{ // Point light

		// TODO: Support multiple lights and multiple light types
		glm::vec3 lightPos;
		CG::PointLight pointLight;

		game.getWorld().view<CG::PointLight, CG::Transform>().each([&](const auto &light, const auto t) {
			pointLight = light;
			lightPos = glm::vec4(static_cast<glm::vec3>(t.position), 1.0);
			});

		onlyshader.uploadUniformVec3("u_pointLight.position", lightPos);
		onlyshader.uploadUniformVec3("u_pointLight.color", pointLight.color.toVec3() * pointLight.intensity);
		onlyshader.uploadUniform1f("u_pointLight.diffuseIntensity", pointLight.diffuseIntensity);
		onlyshader.uploadUniform1f("u_pointLight.specularIntensity", pointLight.specularIntensity);
	}

	// TODO: draw Material by material
#define ADD_RENDERER(type) \
	game.getWorld().view<type, CG::Transform>().each([&](const type &r, const CG::Transform &t) { \
		render(r, t, onlyshader, game.getCamera()); \
		});

	ADD_RENDERER(CG::CubeRenderer);
	ADD_RENDERER(CG::PlaneRenderer);
	ADD_RENDERER(CG::SphereRenderer);
	ADD_RENDERER(CG::MeshRenderer);

#undef ADD_RENDERER
}