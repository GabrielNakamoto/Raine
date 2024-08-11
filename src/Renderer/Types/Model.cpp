#include "Model.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Model::Model(const char* path){

    tinyobj::ObjReaderConfig reader_config;
    /* reader_config.mtl_search_path = ""; */

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(path, reader_config)) {
        if (!reader.Error().empty()) {
            std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty()) {
        std::cout << "TinyObjReader: " << reader.Warning();
    }

    tinyobj::attrib_t attrib = reader.GetAttrib();
    std::vector<tinyobj::shape_t> shapes = reader.GetShapes();
    std::vector<tinyobj::material_t> materials = reader.GetMaterials();

    std::string str = path;
    std::string model_name = str.substr(size_t(str.find_last_of("/")) + 1);
    directory = str.substr(0, str.find_last_of("/") + 1);
    // iterates through every shape / mesh in model
    tinyobj::material_t& mat = materials[0];

    if(!mat.diffuse_texname.empty()){
        textures.push_back(newTexture(mat.diffuse_texname, DIFFUSE));
    }
    if(!mat.specular_texname.empty()){
        textures.push_back(newTexture(mat.specular_texname, SPECULAR));
    }
    if(!mat.bump_texname.empty()){
        textures.push_back(newTexture(mat.bump_texname, NORMAL));
    }

    for(auto& mat : materials){
        Material m = {
            glm::vec3(mat.ambient[0], mat.ambient[1], mat.ambient[2]),
            glm::vec3(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2]),
            glm::vec3(mat.specular[0], mat.specular[1], mat.specular[2]),
            mat.shininess
        };

        mats.push_back(m);

        std::cout << "Loaded material " << mat.name << "\n"
            << "\tAmbience: " << mat.ambient[0] << " " << mat.ambient[1] << " "<< mat.ambient[2] << "\n"
            << "\tDiffuse: " << mat.diffuse[0] << " " << mat.diffuse[1] << " " << mat.diffuse[2] << "\n"
            << "\tSpecular: " << mat.specular[0] << " " << mat.diffuse[1] << " " << mat.diffuse[2] << "\n"
            << "\tShininess: " << mat.shininess << std::endl;
    }

    for(size_t s = 0; s < shapes.size(); s++){
        meshes.push_back(loadMesh(materials, shapes[s].mesh, attrib));
    }

    std::cout << "Loaded model " << model_name << std::endl;

}

Mesh Model::loadMesh(const std::vector<tinyobj::material_t>& materials, const tinyobj::mesh_t& mesh, const tinyobj::attrib_t& attrib){

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // iterates through every face in the mesh
    for(size_t f = 0; f < mesh.num_face_vertices.size(); f++){
        for(size_t v = 0; v < 3; v++){

            Vertex V;

            tinyobj::index_t idx = mesh.indices[f * 3 + v];

            V.position = glm::vec3(
                attrib.vertices[3*size_t(idx.vertex_index)+0],
                attrib.vertices[3*size_t(idx.vertex_index)+1],
                attrib.vertices[3*size_t(idx.vertex_index)+2]
            );

            V.normal = glm::vec3(
                attrib.normals[3*size_t(idx.normal_index)+0],
                attrib.normals[3*size_t(idx.normal_index)+1],
                attrib.normals[3*size_t(idx.normal_index)+2]
            );

            V.texCoord = glm::vec2(
                attrib.texcoords[2*size_t(idx.texcoord_index)+0],
                attrib.texcoords[2*size_t(idx.texcoord_index)+1]
            );

            vertices.push_back(V);
            indices.push_back(idx.vertex_index);
        }
    }

    return Mesh(vertices, indices);
}

Texture Model::newTexture(std::string& filename, texture_t type){
    Texture n_texture = { loadTextureFile(filename), type, filename };
    return n_texture;
}

unsigned int Model::loadTextureFile(std::string& filename){
    unsigned int id;
    glGenTextures(1, &id);
    // load and generate the texture
    int width, height, nrChannels;
    std::string path = directory + filename;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

        std::cout << "Loaded texture " << filename << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture at path " << directory << filename << std::endl;
        stbi_image_free(data);
    }

    return id;
}

void Model::useTextures(){

    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string uniform;

        if(textures[i].type == DIFFUSE){
            uniform = "t_diffuse";
        } else if(textures[i].type == SPECULAR){
            uniform = "t_specular";
        } else if(textures[i].type == NORMAL){
            uniform = "t_normal";
        }

        m_shader->SetInt((uniform).c_str(), i);

        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
}


void Model::Render(){
    assert(m_shader);
    m_shader->Use();
    useTextures();
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Render();
}

void Model::attachShader(ShaderProgram* shader){
    m_shader = shader;
}
