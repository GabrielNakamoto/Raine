#pragma once

#include <memory>
#include "Camera.h"
#include "Renderer/Types/Model.h"

class testState {
private:

    bool wireframe = false;

    Shader* m_vShader = nullptr;
    Shader* m_fShader = nullptr;

    ShaderProgram* m_shaders = nullptr;

    Camera* m_camera = nullptr;
    std::shared_ptr<Model> m_model = nullptr;
    /* Model* m_model = nullptr; */
    Light m_light;

    mat4 m_projection;

public:
    testState();
    ~testState();

    void Update();
};
