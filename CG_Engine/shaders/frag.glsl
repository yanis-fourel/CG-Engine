#version 450 core

in vec3 f_normal;
in vec3 f_pos;

// Material
in vec4 f_surfaceColor;

// Light
flat in vec3 f_ambiantLightColor;
flat in vec4 f_pointLightPosition;
flat in vec3 f_pointLightColor;

// Texture
flat in int f_hasTexture;
in vec2 f_texCoord;
uniform sampler2D f_texture;


out vec4 out_color;


vec3 get_diffuse()
{
    vec3 lightDirection = normalize(vec3(f_pointLightPosition) - f_pos);  
    float diffuseIntensity = max(dot(f_normal, lightDirection), 0.0);

    return f_pointLightColor * diffuseIntensity;
}

void main()
{
    vec4 surfaceColor = f_surfaceColor;

    // branch :( outrageously performant costy
    if (bool(f_hasTexture)) 
        surfaceColor *= texture2D(f_texture, f_texCoord);


    out_color = vec4(f_ambiantLightColor + get_diffuse(), 1) * surfaceColor;
}
