#include "Camera.hpp"

Camera::Camera(PosType position, PosType up, PosType right) noexcept
    : m_position(position), m_up(up), m_right(right)
{
}

glm::mat4 Camera::getViewMatrix() const
{
    glm::vec3 front{ glm::cross(m_up, m_right) };
    glm::vec3 center{ m_position + front };
    glm::mat4 viewMatrix{ glm::lookAt(m_position, center, m_up) };
    return viewMatrix;
}
