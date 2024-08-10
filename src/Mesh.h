#pragma once

#include "Common.h"
#include "ShaderProgram.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};


class Mesh {
private:

    unsigned int VAO, VBO, EBO;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

public:

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void Render();
};
