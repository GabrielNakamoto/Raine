#include "testState.h"
#include "Input/Input.h"
#include "Renderer/Renderer.h"

testState::testState()
: m_camera(new Camera(1.0f, vec3(0.0f, 0.0f, 6.0f), vec3(0.0f, 0.0f, 0.0f))),
  m_light({vec3(1.0f, 2.0f, 6.0f), vec3(0.5f), vec3(0.8f), vec3(0.8f)})
{
    // TODO: use unique pointers

    m_vShader = new Shader("../res/shaders/phong.vert", VERTEX);
    m_fShader = new Shader("../res/shaders/phong.frag", FRAGMENT);

    m_vShader->Compile();
    m_fShader->Compile();

    m_shaders = new ShaderProgram(m_vShader, m_fShader);

    /* m_model = new Model("../res/models/g18/g18.obj"); */
    m_model = new Model("../res/models/backpack/backpack.obj");

    // TODO: BETTER error handling

    m_model->attachShader(m_shaders);

    // TODO: rename to model matrix or smthing
    // TODO: add transform struct

    Renderer::AddModel(m_model);
}

void testState::Update()
{
    if(Input::KeyPressed(GLFW_KEY_H))
        m_shaders->Reload();

    m_shaders->Use();

    m_model->model = mat4(1.0f);
    m_model->model = glm::rotate(m_model->model, glm::radians(static_cast<float>(glfwGetTime()) * glm::radians(1000.0f)), vec3(0.0f, 1.0f, 0.0f));
    /* m_model->model = glm::scale(m_model->model, vec3(0.25f)); */
    m_projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    mat4 view = m_camera->GetViewMatrix();

    m_shaders->SetMat4("projection", m_projection);
    m_shaders->SetMat4("view", view);
    m_shaders->SetMat4("model", m_model->model);

    m_shaders->SetVec3("light.position", m_light.position);
    m_shaders->SetVec3("light.ambient", m_light.ambient);
    m_shaders->SetVec3("light.diffuse", m_light.diffuse);
    m_shaders->SetVec3("light.specular", m_light.specular);
    /* m_shaders->SetMat4("model", m_model->model); */
}

testState::~testState() {
    delete m_model;
    delete m_camera;
    delete m_shaders;
    delete m_vShader;
    delete m_fShader;
}

