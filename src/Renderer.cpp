#include "Renderer.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "Model.h"

#include "stb_image.h"

namespace Renderer {

    Model* backpack = nullptr;
    ShaderProgram* shaders = nullptr;

    glm::mat4 projection;
    glm::mat4 view;

	void Init(){

		Shader* vShader = new Shader("../res/shaders/vertexShader.vert", vertex);
		Shader* fShader = new Shader("../res/shaders/fragmentShader.frag", fragment);

		assert(vShader->Compile());
		assert(fShader->Compile());

		shaders = new ShaderProgram(vShader, fShader);

		delete vShader;
        delete fShader;

        backpack = new Model("../res/models/backpack/backpack.obj");

        backpack->attachShader(shaders);

        /* glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); */
	}

    void RenderFrame(){
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaders->Use();

        backpack->model = glm::mat4(1.0f);
        backpack->model = glm::translate(backpack->model, glm::vec3(0.0f, 0.0f, 0.0f));
        backpack->model = glm::scale(backpack->model, glm::vec3(1.0f, 1.0f, 1.0f));
        backpack->model = glm::rotate(backpack->model, glm::radians((float)glfwGetTime() * glm::radians(1500.0f)), glm::vec3(0.0f, 1.0f, 0.0f));

        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -6.0f));

        shaders->SetMat4("projection", projection);
        shaders->SetMat4("view", view);
        shaders->SetMat4("model", backpack->model);

        backpack->Render();
    }

    void Cleanup(){
        delete backpack;
        delete shaders;
    }
}
