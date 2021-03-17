#version 450 core

// Material?
in vec4 f_surfaceColor;

// Light
flat in vec3 f_ambiantLightColor;

// Texture
flat in int f_hasTexture;
in vec2 f_texCoord;
uniform sampler2D f_texture;


out vec4 out_color;

void main()
{
    vec4 surfaceColor = f_surfaceColor;

    // branch :( outrageously performant costy
    if (bool(f_hasTexture)) 
        surfaceColor *= texture2D(f_texture, f_texCoord);


    out_color = vec4(f_ambiantLightColor, 1) * surfaceColor;
}
