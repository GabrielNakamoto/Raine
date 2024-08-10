#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices)
: vertices(vertices), indices(indices)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    /* glGenBuffers(1, &EBO); */

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

    /* glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); */
    /* glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), */ 
    /*              &indices[0], GL_STATIC_DRAW); */

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

    glBindVertexArray(0);
}

void Mesh::Render(){
    glBindVertexArray(VAO);
    /* glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, 0); */
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}
