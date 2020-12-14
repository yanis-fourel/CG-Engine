#version 450 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec4 v_tint;
layout(location = 3) in vec2 v_texCoord;

uniform mat4 u_model;
uniform mat4 u_viewProj;
uniform mat4 u_modelViewMatrix;
uniform mat3 u_normalMatrix;

uniform vec4 u_pointLightPosition;
uniform vec3 u_pointLightColor;
uniform vec3 u_ambiantLightColor;

uniform float u_materialShininess;
uniform bool u_hasTexture;

out int f_hasTexture;

out vec4 f_surfaceTint;
out vec3 f_surfaceNormal;
out vec3 f_surfacePosition;
out vec2 f_texCoord;

out vec3 f_ambiantLightColor;
out vec3 f_pointLightPosition;
out vec3 f_pointLightColor;

out float f_materialShininess;


void main()
{
    gl_Position = u_viewProj * u_model * vec4(v_position, 1.0);

    f_texCoord = v_texCoord;

    f_surfaceTint = v_tint;
    f_surfaceNormal = normalize(u_normalMatrix * v_normal);
    f_surfacePosition = vec3(u_modelViewMatrix * vec4(v_position, 1.0));
    f_texCoord = v_texCoord;

    f_ambiantLightColor = u_ambiantLightColor;
    f_pointLightPosition = vec3(u_pointLightPosition);
    f_pointLightColor = u_pointLightColor;

    f_materialShininess = u_materialShininess;

    f_hasTexture = int(u_hasTexture);
}
