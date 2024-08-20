#include "Renderer.h"
#include "../BackEnd/Types/ShaderProgram.h"
#include "../BackEnd/Types/Shader.h"
#include "RendererCommon.h"
#include "Types/Model.h"
#include "../Camera.h"
#include "../Input/Input.h"

#include "stb_image.h"

// pass path names into shaderprogram

namespace Renderer {

    vector<Model*> models;

    void RenderFrame(){
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(auto& model : models)
            if(model) model->Render();
    }

    void AddModel(Model* model){
        models.push_back(model);
    }
}
