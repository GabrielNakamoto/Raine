#version 410 core

out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D t_diffuse;
uniform sampler2D t_specular;
uniform sampler2D t_normal;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material mat;

void main(){

    // make uniforms?
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 lightSource = vec3(1.0f, 1.0f, 1.0f);
    vec3 viewPos = vec3(0.0f, 0.0f, 6.0f);

    float ambientStrength = 0.1;
    float specularStrength = 0.5;

    vec3 normalMap = texture(t_normal, texCoord).rgb;
    normalMap = normalMap * 2.0f - 1.0f;

    vec3 norm = normalize(normalMap);
    // vec3 norm = normalize(normal);
    vec3 lightDir = lightSource - fragPos;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0f), 8) * specularStrength * lightColor;

    vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor;

    vec3 ambient = ambientStrength * lightColor;

    vec4 result = vec4((ambient + diffuse), 1.0f);

    FragColor = texture(t_diffuse, texCoord) * result;
    // FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
