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


// -- OUT ---------------------

// Material?
out vec4 f_surfaceColor;

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

    // Material?
    f_surfaceColor = v_color;
    
    // Light
    f_ambiantLightColor = u_ambiantLightColor;

    // Texture
    f_texCoord = v_texCoord;
    f_hasTexture = int(u_hasTexture);
}
