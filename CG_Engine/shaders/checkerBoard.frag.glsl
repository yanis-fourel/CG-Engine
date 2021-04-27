#version 450 core

in vec3 f_normal;
in vec3 f_pos;
in vec3 f_color;

uniform vec3 u_color1;
uniform vec3 u_color2;
uniform vec3 u_size;

uniform float u_shininess;
uniform float u_ambiantFact;
uniform float u_diffuseFact;
uniform float u_specularFact;

uniform vec3 u_eyePos;

// Light
struct PointLight {
    vec3 position;

    vec3 color;
    float diffuseIntensity;
    float specularIntensity;
};

uniform PointLight u_pointLight;
uniform vec3 u_ambiantLightColor;



out vec4 out_color;

// -------------------------------------------------------------

vec3 get_ambiant(vec3 tileColor)
{
    return u_ambiantLightColor * tileColor * u_ambiantFact;
}

vec3 get_diffuse(vec3 tileColor)
{
    vec3 surfaceDiffuse = tileColor * u_diffuseFact;

    vec3 lightDir = normalize(vec3(u_pointLight.position) - f_pos);  
    float intensity = max(dot(f_normal, lightDir), 0.0);


    return intensity * u_pointLight.diffuseIntensity * u_pointLight.color * surfaceDiffuse;
}

vec3 get_specular(vec3 tileColor)
{
    vec3 surfaceSpecular = tileColor * u_specularFact;

    vec3 lightDir = normalize(vec3(u_pointLight.position) - f_pos);  
    vec3 viewDir = normalize(u_eyePos - f_pos);
    vec3 reflectDir = reflect(-lightDir, f_normal);  

    float intensity = pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);
    return intensity * u_pointLight.specularIntensity * u_pointLight.color * u_pointLight.specularIntensity * surfaceSpecular;  
}

void main()
{   
    vec3 tileColor;

    // This is more performant than my best branchless attempt
    if (mod(round(f_pos.x) + round(f_pos.y / u_size.y) + round(f_pos.z / u_size.z), 2) < 1)
        tileColor = u_color1;
    else
        tileColor = u_color2;


    vec3 result = (get_ambiant(tileColor) + get_diffuse(tileColor) + get_specular(tileColor)) * f_color;
    out_color = vec4(result, 1);
}
