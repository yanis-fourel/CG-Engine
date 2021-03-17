#version 450 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec4 v_color;
layout(location = 3) in vec2 v_texCoord;

uniform mat4 u_model;
uniform mat4 u_viewProj;
uniform mat4 u_modelViewMatrix;
uniform mat3 u_normalMatrix;

uniform vec3 u_ambiantLightColor;
uniform vec4 u_pointLightPosition;
uniform vec3 u_pointLightColor;

// -- OUT ---------------------

out vec3 f_normal;
out vec3 f_pos;

// Material
out vec4 f_surfaceColor;
out vec4 f_pointLightPosition;
out vec3 f_pointLightColor;

// Light 
out vec3 f_ambiantLightColor;

// Texture
out int f_hasTexture;
out vec2 f_texCoord;
uniform bool u_hasTexture;

// ----------------------------

void main()
{
    gl_Position = u_viewProj * u_model * vec4(v_position, 1.0);

    f_pos = vec3(u_model * vec4(v_position, 1.0));

    f_normal = normalize(v_normal); // we normalize again to be certain

    // Material?
    f_surfaceColor = v_color;
    
    // Light
    f_ambiantLightColor = u_ambiantLightColor;
    f_pointLightPosition = u_pointLightPosition;
    f_pointLightColor = u_pointLightColor;

    // Texture
    f_texCoord = v_texCoord;
    f_hasTexture = int(u_hasTexture);
}
