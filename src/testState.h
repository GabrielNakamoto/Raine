#pragma once

#include <memory>
#include "Camera.h"
#include "Renderer/Types/Model.h"

class testState {
private:

    Shader* m_vShader = nullptr;
    Shader* m_fShader = nullptr;

    ShaderProgram* m_shaders = nullptr;

    Camera* m_camera = nullptr;
    Model* m_model = nullptr;
    Light m_light;

    mat4 m_projection;

public:
    testState();
    ~testState();

    void Update();
};
