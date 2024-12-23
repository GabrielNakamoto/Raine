#include "Renderer.h"
#include "../BackEnd/Types/ShaderProgram.h"
#include "../BackEnd/Types/Shader.h"
#include "RendererCommon.h"
#include "Types/Model.h"
#include "../Camera.h"
#include "../Input/Input.h"

#include "stb_image.h"

/* #include <memory> */
// pass path names into shaderprogram

namespace Renderer {

    vector<std::shared_ptr<Model>> models;

    void RenderFrame(){
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        for(auto& model : models)
            if(model) model->Render();
    }

    // copy constructs a new pointer to same object
    void AddModel(std::shared_ptr<Model> model){
        models.push_back(model);
    }
}
