#version 410 core

out vec4 FragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform sampler2D t_diffuse;
uniform sampler2D t_specular;
uniform sampler2D t_normal;
uniform sampler2D t_displace;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define MAX_MATERIALS 5

uniform Material materials[MAX_MATERIALS];
uniform Light light;

void main(){
    vec3 viewPos = vec3(0.0f, 0.0f, 6.0f);

    vec3 normalMap = texture(t_normal, texCoord).rgb;
    normalMap = normalMap * 2.0f - 1.0f;

    vec3 norm = normalize(normalMap);

    vec3 lightDir = normalize(light.position - fragPos);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 250);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 specular = light.specular * spec * vec3(texture(t_specular, texCoord).r);
    vec3 diffuse = light.diffuse * diff * texture(t_diffuse, texCoord).rgb;
    vec3 ambient = light.ambient * texture(t_diffuse, texCoord).rgb;

    vec4 result = vec4((ambient + diffuse + specular), 1.0f);
    // vec4 result = vec4(vec3(texture(t_normal, texCoord).rgb), 1.0f);
    // vec4 result = vec4(1.0f, 0.0f, 0.0f, 1.0f);

    FragColor = result;
}
