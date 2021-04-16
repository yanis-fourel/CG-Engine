#include <entt/entt.hpp>
#include <ranges>
#include <spdlog/spdlog.h>

#include "CG/rendering/RenderSystem.hpp"
#include "CG/rendering/RendererHelper.hpp"

#include "CG/components/PointLight.hpp"

#include "CG/components/renderer/_all.hpp"

#include "CG/rendering/materials/MaterialSolid.hpp"


void CG::Renderer::renderScene(const AGame &game) noexcept
{
	detail::uploadGlobalUniforms(game);

	// TODO: Mesh rendering maintenance. untested since several refact
	auto viewMR = game.getWorld().view<CG::MeshRenderer, CG::Transform>();
	viewMR.each([&](const MeshRenderer &mr, const auto &transform) {
		const auto &usedShader = getMaterialShader<CG::material::Solid>();
		uploadModelMatrixes(usedShader, transform, game.getCamera());
		mr.draw(usedShader);
		});


	// TODO: support other renderer transparency + performance optimisation

	std::vector<std::pair<const CG::ShapeRenderer *, CG::Transform>> transparentShapes;

	auto viewSR = game.getWorld().view<CG::ShapeRenderer, CG::Transform>();
	viewSR.each([&](const ShapeRenderer &sr, const auto &transform) {
		if (sr.hasTransparence()) // Terrible branching
			transparentShapes.push_back(std::make_pair(&sr, transform));
		else {
			uploadModelMatrixes(sr.material->getShader(), transform, game.getCamera());
			sr.draw();
		}
		});


	std::ranges::sort(transparentShapes, [&](const auto &lhs, const auto &rhs) {
		return CG::Vector3::distance(lhs.second.position, game.getCamera().getPosition())
			> CG::Vector3::distance(rhs.second.position, game.getCamera().getPosition());
		});

	for (const auto &[sr, transform] : transparentShapes) {
		uploadModelMatrixes(sr->material->getShader(), transform, game.getCamera());
		sr->draw();
	}
}

void CG::Renderer::detail::uploadGlobalUniforms(const AGame &game) noexcept
{
	std::vector<const ShaderProgram *> allShaders = {
		&getMaterialShader<::CG::material::Solid>()
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
