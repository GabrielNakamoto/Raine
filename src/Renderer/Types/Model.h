#pragma once

#include "../../Common.h"
#include "../RendererCommon.h"
#include "../../BackEnd/Types/ShaderProgram.h"
#include "Mesh.h"

#include "tiny_obj_loader.h"

class Model {
private:

    ShaderProgram* m_shader = nullptr;

    std::string directory;
    std::vector<Mesh> meshes;
    std::vector<Texture> textures;
    std::vector<Material> mats;

    Mesh loadMesh(const std::vector<tinyobj::material_t>& materials, const tinyobj::mesh_t& mesh, const tinyobj::attrib_t& attrib);
    Texture newTexture(std::string& filename, texture_t type);
    unsigned int loadTextureFile(std::string& filename);

    void useTextures();

public:

    glm::mat4 model;

    Model(const char* path);
    void attachShader(ShaderProgram* shader);
    void Render();
};
