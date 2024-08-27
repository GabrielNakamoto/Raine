#pragma once

#include "../../Common.h"
#include "../RendererCommon.h"

struct Mesh {
private:

    unsigned int VAO, VBO, EBO;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Material m_mat;

public:

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
    void Render();
};
