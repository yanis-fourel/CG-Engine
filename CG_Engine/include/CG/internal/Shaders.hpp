#pragma once

#include <string_view>

namespace CG::shaders {

constexpr std::string_view simple_frag = R"(
#version 450 core

in vec4 f_surfaceColor;
in vec3 f_surfaceNormal;
in vec3 f_surfacePosition;

flat in vec3 f_ambiantLightColor;

flat in vec3 f_pointLightPosition;
flat in vec3 f_pointLightColor;

flat in float f_materialShininess;

out vec4 color;

float lightAttenuationFactor(float dist)
{
    return 1 / pow(dist, 2);
}

void main()
{
    const vec3 L = normalize(vec3(f_pointLightPosition) - f_surfacePosition);
    const vec3 R = reflect(-L, f_surfaceNormal);

    const float distanceSurfaceLight = distance(f_pointLightPosition, f_surfacePosition);
    const float distanceSurfaceEye = length(f_surfacePosition);

    const float diffuseLightColorAttenuation = lightAttenuationFactor(distanceSurfaceLight);
    const float specularLightColorAttenuation = lightAttenuationFactor(distanceSurfaceLight + distanceSurfaceEye);

    const float dotLN = max(0, dot(f_surfaceNormal, L));
    const float dotRPos = max(0, dot(R, -f_surfacePosition));
    
    const vec3 diffuseLightColor =  diffuseLightColorAttenuation * f_pointLightColor * dotLN;
    const vec3 specularLightColor = specularLightColorAttenuation * f_pointLightColor * pow(dotRPos, f_materialShininess);

    color = f_surfaceColor * vec4(f_ambiantLightColor + diffuseLightColor + specularLightColor, 1.0);
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

uniform vec4 u_pointLightPosition;
uniform vec3 u_pointLightColor;
uniform vec3 u_ambiantLightColor;

uniform float u_materialShininess;

out vec4 f_surfaceColor;
out vec3 f_surfaceNormal;
out vec3 f_surfacePosition;

out vec3 f_ambiantLightColor;
out vec3 f_pointLightPosition;
out vec3 f_pointLightColor;

out float f_materialShininess;


void main()
{
    gl_Position = u_viewProj * u_model * vec4(v_position, 1.0);

    f_surfaceColor = v_color;
    f_surfacePosition = vec3(u_modelViewMatrix * vec4(v_position, 1.0));
    f_surfaceNormal = normalize(u_normalMatrix * v_normal);

    f_ambiantLightColor = u_ambiantLightColor;
    f_pointLightPosition = vec3(u_pointLightPosition);
    f_pointLightColor = u_pointLightColor;

    f_materialShininess = u_materialShininess;
}

)";

}
