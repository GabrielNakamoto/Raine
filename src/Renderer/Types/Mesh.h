#pragma once

#include "../../Common.h"
#include "../RendererCommon.h"

class Mesh {
private:

    unsigned int VAO, VBO, EBO;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Material m_mat;

public:

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void Render();
};
