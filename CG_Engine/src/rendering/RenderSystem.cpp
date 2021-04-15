#include <entt/entt.hpp>
#include <ranges>
#include <spdlog/spdlog.h>

#include "CG/rendering/RenderSystem.hpp"
#include "CG/rendering/RendererHelper.hpp"

#include "CG/components/PointLight.hpp"

#include "CG/components/renderer/_all.hpp"

#include "CG/components/material/MaterialSolid.hpp"


struct mat_trans { entt::entity entity; ::CG::AMaterial *material; ::CG::Transform *transform; };
using DisplayableBuffer = std::vector<mat_trans>;

template <typename TMaterial>
void displayOrBufferize(const CG::AGame &game, DisplayableBuffer &tranparents)
{
	game.getWorld().view<TMaterial, ::CG::Transform>().each(
		[&](auto e, auto &material, auto &transform) {
			if (material.hasTransparence())
				tranparents.push_back({ e, &material, &transform });
			else {
				CG::Renderer::detail::display(game, e, material, transform);
			}
		});
}

void CG::Renderer::renderScene(const AGame &game) noexcept
{
	detail::uploadGlobalUniforms(game);


	// TODO: Get two collections of AMaterial *, tranparent and non-transparent (cache optimizable), opti : entt::observer observer{registry, entt::collector.update<...>()};
	// Display non transparent quickly
	// Sort transparent by distance(camera, obj center)
	// display from furthest to closest


	DisplayableBuffer transparents;

	displayOrBufferize<::CG::MaterialSolid>(game, transparents);
	// ....


	std::ranges::sort(transparents, [&](const auto &lhs, const auto &rhs) {
		return CG::Vector3::distance(lhs.transform->position, game.getCamera().getPosition())
			> CG::Vector3::distance(rhs.transform->position, game.getCamera().getPosition());
		});

	for (auto &[entity, material, transform] : transparents)
		detail::display(game, entity, *material, *transform);

}

void CG::Renderer::detail::uploadGlobalUniforms(const AGame &game) noexcept
{
	std::vector<const ShaderProgram *> allShaders = {
		&getMaterialShader<::CG::MaterialSolid>()
	};

	// TODO: Support multiple lights and multiple light types
	glm::vec3 lightPos;
	::CG::PointLight pointLight;

	game.getWorld().view<::CG::PointLight, ::CG::Transform>().each([&](const auto &light, const auto t) {
		pointLight = light;
		lightPos = glm::vec4(static_cast<glm::vec3>(t.position), 1.0);
		});



	// TODO: shared uniforms (uniform that would be shared across every shader, if possible?)
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



void CG::Renderer::detail::display(const AGame &game, entt::entity entity, const ::CG::AMaterial &material, const ::CG::Transform &transform) noexcept
{
	material.getShader().use();
	material.uploadUniforms();


	// TODO: omfg find a better way for the love of god

	if (auto *renderer = game.getWorld().try_get<CG::SphereRenderer>(entity))
		render(*renderer, transform, material.getShader(), game.getCamera());
	else if (auto *renderer = game.getWorld().try_get<CG::CubeRenderer>(entity))
		render(*renderer, transform, material.getShader(), game.getCamera());
	else if (auto *renderer = game.getWorld().try_get<CG::PlaneRenderer>(entity))
		render(*renderer, transform, material.getShader(), game.getCamera());
	else if (auto *renderer = game.getWorld().try_get<CG::MeshRenderer>(entity))
		render(*renderer, transform, material.getShader(), game.getCamera());
	else
		spdlog::error("No renderer for entity with material ...");
}
