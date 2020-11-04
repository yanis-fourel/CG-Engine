#version 450 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec4 v_color;

uniform mat4 model;
uniform mat4 viewProj;

out vec4 f_color;

void main()
{
    gl_Position = viewProj * model * vec4(v_position.x, v_position.y, v_position.z, 1.0);
    f_color = v_color;
}
