#include <entt/entt.hpp>

#include "CG/rendering/RenderSystem.hpp"

#include "CG/components/PointLight.hpp"
#include "CG/components/Transform.hpp"

#include "CG/components/renderer/_all.hpp"

#include "CG/rendering/RendererHelper.hpp"

void CG::Renderer::renderScene(const AGame &game) noexcept
{
	detail::uploadGlobalUniforms(game);


	// TODO: Get two collections of AMaterial *, tranparent and non-transparent (cache optimizable), opti : entt::observer observer{registry, entt::collector.update<...>()};
	// Display non transparent quickly
	// Sort transparent by distance(camera, obj center)
	// display from furthest to closest



// TODO: use template instead of macro wtf
//#define ADD_RENDERER(type) \
//	game.getWorld().view<type, CG::Transform>().each([&](const type &r, const CG::Transform &t) { \
//		render(r, t, onlyshader, game.getCamera()); \
//		});
//
//	ADD_RENDERER(CG::CubeRenderer);
//	ADD_RENDERER(CG::PlaneRenderer);
//	ADD_RENDERER(CG::SphereRenderer);
//	ADD_RENDERER(CG::MeshRenderer);
//
//#undef ADD_RENDERER
}

void CG::Renderer::detail::uploadGlobalUniforms(const AGame &game) noexcept
{
	// TODO: shared uniforms (uniform that would be shared across every shader, if possible?)

	std::vector<const ShaderProgram *> allShaders = {

	};

	// TODO: Support multiple lights and multiple light types
	glm::vec3 lightPos;
	CG::PointLight pointLight;

	game.getWorld().view<CG::PointLight, CG::Transform>().each([&](const auto &light, const auto t) {
		pointLight = light;
		lightPos = glm::vec4(static_cast<glm::vec3>(t.position), 1.0);
		});

	for (auto &shader : allShaders) {

		shader->use();

		shader->uploadUniformMat4("u_viewProj", game.getCamera().getViewProjMatrix());
		shader->uploadUniformVec3("u_ambiantLightColor", game.getAmbiantLight().toVec3());
		shader->uploadUniformVec3("u_eyePos", game.getCamera().getPosition());

		shader->uploadUniformVec3("u_pointLight.position", lightPos);
		shader->uploadUniformVec3("u_pointLight.color", pointLight.color.toVec3() * pointLight.intensity);
		shader->uploadUniform1f("u_pointLight.diffuseIntensity", pointLight.diffuseIntensity);
		shader->uploadUniform1f("u_pointLight.specularIntensity", pointLight.specularIntensity);
	}
}
