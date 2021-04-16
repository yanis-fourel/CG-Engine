#version 450 core

layout(location = 0) in float v_posLerp;

uniform mat4 u_viewProj;

uniform vec3 u_p1;
uniform vec3 u_p2;



void main()
{
    gl_Position = u_viewProj * vec4(mix(u_p1, u_p2, v_posLerp), 1.0);
}
