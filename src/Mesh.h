#pragma once

#include "Common.h"
#include "ShaderProgram.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

enum texture_t {
    DIFFUSE = 0,
    SPECULAR = 1
};

struct Texture {
    unsigned int id;
    texture_t type;
    std::string path;
};

class Mesh {
private:

    unsigned int VAO, VBO, EBO;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

public:

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Render(ShaderProgram* shader);
};
