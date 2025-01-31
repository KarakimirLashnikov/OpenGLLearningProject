#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far)
    :Camera(), m_fovy(fovy), m_aspect(aspect), m_near(near), m_far(far)
{
}

glm::mat4 PerspectiveCamera::getProjectionMatrix() const
{
    glm::mat4 proj{
        glm::perspective(glm::radians(m_fovy), m_aspect, m_near, m_far)
    };
    return proj;
}
