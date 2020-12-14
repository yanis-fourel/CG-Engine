#version 450 core

in vec4 f_surfaceTint;
in vec3 f_surfaceNormal;
in vec3 f_surfacePosition;
in vec2 f_texCoord;

flat in vec3 f_ambiantLightColor;

flat in vec3 f_pointLightPosition;
flat in vec3 f_pointLightColor;

flat in float f_materialShininess;

flat in int f_hasTexture;

uniform sampler2D f_texture;


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

    vec4 surfaceColor = f_surfaceTint;

    // branch :( outrageously performant costy
    if (bool(f_hasTexture)) 
        surfaceColor *= texture2D(f_texture, f_texCoord);

    color = vec4(specularLightColor, 1.0) + surfaceColor * vec4(f_ambiantLightColor + diffuseLightColor, 1.0);
//    color = surfaceColor;
}
