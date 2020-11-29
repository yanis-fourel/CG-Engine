#pragma once

#include <string_view>

namespace CG::shaders {

	constexpr std::string_view simple_frag = R"(
#version 450 core

in vec4 f_outColor;
in vec3 f_surfaceNormal;

out vec4 color;

void main()
{
    f_surfaceNormal;

    color = f_outColor;
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

uniform vec4 u_lightPosition;
uniform vec3 u_pointLightColor;
uniform vec3 u_ambiantLightColor;

out vec4 f_outColor;
out vec3 f_surfaceNormal;

void main()
{
    const float shininess = 0.8;

    gl_Position = u_viewProj * u_model * vec4(v_position.x, v_position.y, v_position.z, 1.0);

    f_surfaceNormal = normalize(u_normalMatrix * v_normal);

    vec3 vertexPosition = vec3(u_modelViewMatrix * vec4(v_position, 1.0));

    vec3 normal = f_surfaceNormal;
    vec3 L = normalize(vec3(u_lightPosition) - vertexPosition);
    vec3 R = reflect(-L, normal);
    

    float dotLN = max(0, dot(normal, L));
    float dotRPos = max(0, dot(R, -vertexPosition));
    
    vec3 diffuseLightColor = u_pointLightColor * dotLN;
    vec3 specularLightColor = u_pointLightColor * pow(dotRPos, shininess);

    f_outColor = v_color * vec4(u_ambiantLightColor + diffuseLightColor + specularLightColor, 1.0);
}

)";

}
