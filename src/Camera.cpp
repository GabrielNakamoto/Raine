#include "Camera.h"

Camera::Camera(float speed, const vec3& position, const vec3& target = vec3(0.0f))
: m_position(position), m_speed(speed)
{
    /* m_front = glm::normalize(position - target); */
    m_front = vec3(0.0f, 0.0f, -1.0f);
    m_up = vec3(0.0f, 1.0f, 0.0f);
    /* m_right = glm::normalize(glm::cross(vec3(0.0f, 1.0f, 0.0f), m_front)); */
    /* m_up = glm::cross(m_front, m_right); */
};

mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}
