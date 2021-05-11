#version 450 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec4 v_color;
layout(location = 3) in vec2 v_texCoord;

uniform mat4 u_model;
uniform mat4 u_viewProj;
uniform mat3 u_normalMatrix;

out vec3 f_normal;
out vec3 f_pos;
out vec3 f_color;
out vec2 f_texCoord;

void main()
{
    gl_Position = u_viewProj * u_model * vec4(v_position, 1.0);

    f_pos = vec3(u_model * vec4(v_position, 1.0));
    f_normal = normalize(u_normalMatrix * v_normal);
    f_color = vec3(v_color);
    f_texCoord = v_texCoord;
}
