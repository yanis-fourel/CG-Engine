#pragma once

#include <string_view>

namespace CG::shaders {

	constexpr std::string_view simple_frag = R"(
#version 450 core

in vec4 f_surfaceColor;
in vec3 f_surfaceNormal;

out vec4 color;

void main()
{
    f_surfaceNormal;

    color = f_surfaceColor;
}
)";

	constexpr std::string_view simple_vert = R"(
#version 450 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec4 v_color;

uniform mat4 u_model;
uniform mat4 u_viewProj;
uniform mat4 u_modelViewMatrix;
uniform mat3 u_normalMatrix;

out vec4 f_surfaceColor;
out vec3 f_surfaceNormal;

void main()
{
    gl_Position = u_viewProj * u_model * vec4(v_position.x, v_position.y, v_position.z, 1.0);

    f_surfaceNormal = normalize(u_normalMatrix * v_normal);
    f_surfaceColor = v_color;

    u_modelViewMatrix;
}

)";

}
