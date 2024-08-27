#pragma once

#include "Renderer/RendererCommon.h"

class Camera {
public:
    vec3 m_position;
    vec3 m_front;
    vec3 m_right;
    vec3 m_up;
    vec3 worldUp;

    float m_speed;

    Camera(float speed, const vec3& position, const vec3& target);
    ~Camera() = default;
    mat4 GetViewMatrix();
};
