#pragma once

//#include <iostream>
//#include "CG/utils/glmMatrixFormat.hpp"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "CG/rendering/ShaderProgram.hpp"
#include "CG/Camera.hpp"

namespace CG::Renderer
{

inline void uploadModelMatrixes(const ShaderProgram &sp, const CG::Transform &t, const Camera &c) noexcept
{
	glm::mat4 model;

	{
		auto rot = static_cast<glm::quat>(t.rotation);
		auto rotationMatrix		= glm::toMat4(glm::quat(-rot.w, rot.x, -rot.y, rot.z));

		auto translationMatrix	= glm::translate(static_cast<glm::vec3>(t.position));
		auto scalingMatrix		= glm::scale(static_cast<glm::vec3>(t.scale));


		model = translationMatrix * rotationMatrix * scalingMatrix;
	}


	Vector3 n1 = t.rotation * Vector3::Up();
	Vector3 n2 = static_cast<glm::vec3>(Vector3::Up()) * glm::toMat3(static_cast<glm::quat>(t.rotation));
	Vector3 n3 = static_cast<glm::vec3>(Vector3::Up()) * glm::mat3(glm::transpose(glm::inverse(glm::mat3(model))));

	//std::cout << model << std::endl;

	Vector3 p1 = t.rotation * Vector3(0, 0, 1);
	Vector3 p2 = glm::vec3(glm::vec4(0, 0, 0.001, 1) * model);


	sp.uploadUniformMat4("u_model", model);
	sp.uploadUniformMat3("u_normalMatrix", glm::transpose(glm::inverse(glm::mat3(model))));
}

}