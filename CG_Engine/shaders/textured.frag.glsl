#version 450 core

in vec3 f_normal;
in vec3 f_pos;
in vec3 f_color;
in vec2 f_texCoord;

uniform vec3 u_eyePos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float opacity;
};

uniform Material u_material;

// Light

struct PointLight {
    vec3 position;

    vec3 color;
    float diffuseIntensity;
    float specularIntensity;
};

uniform PointLight u_pointLight;
uniform vec3 u_ambiantLightColor;

uniform sampler2D f_texture;

out vec4 out_color;

// -------------------------------------------------------------

vec3 get_ambiant()
{
    return u_ambiantLightColor * u_material.ambient;
}

vec3 get_diffuse()
{
    vec3 lightDir = normalize(vec3(u_pointLight.position) - f_pos);  
    float intensity = max(dot(f_normal, lightDir), 0.0);

    return  intensity * u_pointLight.diffuseIntensity * u_pointLight.color * u_material.diffuse;
}

vec3 get_specular()
{
    vec3 lightDir = normalize(vec3(u_pointLight.position) - f_pos);  
    vec3 viewDir = normalize(u_eyePos - f_pos);
    vec3 reflectDir = reflect(-lightDir, f_normal);  

    float intensity = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    return intensity * u_pointLight.specularIntensity * u_pointLight.color * u_material.specular;  
}

void main()
{
    vec4 surfaceColor = vec4(f_color, 1) * texture2D(f_texture, f_texCoord);
    out_color = vec4(get_ambiant() + get_diffuse() + get_specular(), 1) * surfaceColor;
}
