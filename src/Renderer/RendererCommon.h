#pragma once

#include "../Common.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::vec2;
using glm::vec3;

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

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

enum texture_t {
    DIFFUSE = 0,
    SPECULAR = 1,
    NORMAL = 2
};

struct Texture {
    unsigned int id;
    texture_t type;
    string path;
};


