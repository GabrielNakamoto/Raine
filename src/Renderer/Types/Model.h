#pragma once

#include "../../Common.h"
#include "../RendererCommon.h"
#include "../../BackEnd/Types/ShaderProgram.h"
#include "Mesh.h"

#include "tiny_obj_loader.h"

struct Model {
private:

    ShaderProgram* m_shader = nullptr;

    string directory;
    vector<Mesh> meshes;
    // replace with specific textures?
    // m_albedo etc..
    vector<Texture> textures;
    vector<Material> mats;

    Mesh loadMesh(const std::vector<tinyobj::material_t>& materials, const tinyobj::mesh_t& mesh, const tinyobj::attrib_t& attrib);
    Texture newTexture(std::string& filename, texture_t type);
    unsigned int loadTextureFile(const std::string& filename);

    void useTextures();

public:

    mat4 model;

    Model(const char* path);
    void attachShader(ShaderProgram* shader);
    void Render();
};
