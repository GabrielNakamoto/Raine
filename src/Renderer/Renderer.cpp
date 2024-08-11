#include "Renderer.h"
#include "../BackEnd/Types/ShaderProgram.h"
#include "../BackEnd/Types/Shader.h"
#include "RendererCommon.h"
#include "Types/Model.h"

#include "../Input/Input.h"

#include "stb_image.h"

namespace Renderer {

    Model* backpack = nullptr;
    ShaderProgram* shaders = nullptr;

    glm::mat4 projection;
    glm::mat4 view;
    Shader* vShader = new Shader("../res/shaders/phong.vert", VERTEX);
    Shader* fShader = new Shader("../res/shaders/phong.frag", FRAGMENT);

    Light light = {
        vec3(1.0f, 2.0f, 6.0f), // pos
        vec3(1.0f), // ambient
        vec3(0.8f), // diffuse
        vec3(1.0f)  // specular
    };

	void Init(){


		assert(vShader->Compile());
		assert(fShader->Compile());

		shaders = new ShaderProgram(vShader, fShader);

		/* delete vShader; */
        /* delete fShader; */

        /* backpack = new Model("../res/models/backpack/backpack.obj"); */
        backpack = new Model("../res/models/g18/g18.obj");

        backpack->attachShader(shaders);

        /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
	}

    void RenderFrame(){
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaders->Use();

        backpack->model = glm::mat4(1.0f);
        backpack->model = glm::translate(backpack->model, glm::vec3(0.0f, 0.0f, 0.0f));
        backpack->model = glm::scale(backpack->model, glm::vec3(0.25f));
        /* backpack->model = glm::scale(backpack->model, glm::vec3(1.0f)); */
        backpack->model = glm::rotate(backpack->model, glm::radians((float)glfwGetTime() * glm::radians(1500.0f)), glm::vec3(0.0f, 1.0f, 0.0f));

        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -6.0f));

        shaders->SetMat4("projection", projection);
        shaders->SetMat4("view", view);
        shaders->SetMat4("model", backpack->model);

        shaders->SetVec3("light.position", light.position);
        shaders->SetVec3("light.ambient", light.ambient);
        shaders->SetVec3("light.diffuse", light.diffuse);
        shaders->SetVec3("light.specular", light.specular);

        backpack->Render();

        if(Input::KeyPressed(GLFW_KEY_H))
            shaders->Reload();
    }

    void Cleanup(){
        delete backpack;
        delete shaders;
        delete vShader;
        delete fShader;
    }
}
