#include "Camera.hpp"

Camera::Camera(PosType position, PosType up, PosType front) noexcept
    : m_position(position), m_up(up), m_front(front)
{
}

glm::mat4 Camera::getViewMatrix() const
{
    glm::vec3 center{ m_position + m_front };
    glm::mat4 viewMatrix{ glm::lookAt(m_position, center, m_up) };
    return viewMatrix;
}

glm::vec3 Camera::getPosition() const noexcept
{
    return this->m_position;
}
