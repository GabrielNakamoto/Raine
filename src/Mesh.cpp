#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
: vertices(vertices), indices(indices), textures(textures)
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

void Mesh::Render(ShaderProgram* shader){
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string name, number;
        if(textures[i].type == DIFFUSE){
            name = "texture_diffuse";
            number = std::to_string(diffuseNr++);
        } else if(textures[i].type == SPECULAR){
            name = "texture_specular";
            number = std::to_string(specularNr++);
        }

        shader->SetInt((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    // draw mesh
    glBindVertexArray(VAO);
    /* glDrawElements(GL_TRIANGLES, vertices.size(), GL_UNSIGNED_INT, 0); */
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}
