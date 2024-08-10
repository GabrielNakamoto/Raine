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
        textures_loaded.push_back(newTexture(mat.diffuse_texname, DIFFUSE));
    }
    if(!mat.specular_texname.empty()){
        textures_loaded.push_back(newTexture(mat.specular_texname, SPECULAR));
    }

    for(size_t s = 0; s < shapes.size(); s++){
        meshes.push_back(loadMesh(materials, shapes[s].mesh, attrib));
    }


    std::cout << "Loaded model " << model_name << std::endl;
}

Mesh Model::loadMesh(const std::vector<tinyobj::material_t>& materials, const tinyobj::mesh_t& mesh, const tinyobj::attrib_t& attrib){

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    std::vector<bool> mat_ids_loaded(materials.size(), false);

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

        /* if(!materials.empty()){} */
        /* if(!mat_ids_loaded[mesh.material_ids[f]]){ */
        /*     mat_ids_loaded[mesh.material_ids[f]] = true; */

        /*     tinyobj::material_t mat = materials[mesh.material_ids[f]]; */
        /*     /1* if(mat.diffuse_texname.empty()) *1/ */
        /*     /1*     return Mesh(vertices, indices); *1/ */

        /*     for(size_t t = 0; t < textures_loaded.size(); t++){ */
        /*         if(textures_loaded[t].path == mat.diffuse_texname) */
        /*             textures.push_back(textures_loaded[t]); */

        /*         if(textures_loaded[t].path == mat.specular_texname) */
        /*             textures.push_back(textures_loaded[t]); */
        /*     } */
        /* } */
    }
    textures = textures_loaded;

    return Mesh(vertices, indices, textures);
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


void Model::Render(){
    assert(m_shader);
    m_shader->Use();
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].Render(m_shader);
}

void Model::attachShader(ShaderProgram* shader){
    m_shader = shader;
}
