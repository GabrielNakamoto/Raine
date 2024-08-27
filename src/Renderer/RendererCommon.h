#pragma once

#include "../Common.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::vec2;
using glm::vec3;
using glm::mat4;

struct Vertex {
    vec3 position;
    vec3 normal;
    vec2 texCoord;
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
    DIFFUSE,
    SPECULAR,
    NORMAL,
    DISPLACEMENT
};

struct Texture {
    unsigned int id;
    texture_t type;
    string path;
};


