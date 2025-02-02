#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float, float,
    PosType position, PosType up, PosType front)
    : m_fovy(fovy), m_aspect(aspect), m_near(0.1f), m_far(1000.0f),
    Camera(position, up, front)
{
}

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float, float)
    : m_fovy(fovy), m_aspect(aspect), m_near(0.1f), m_far(1000.0f),
    Camera()
{
}

glm::mat4 PerspectiveCamera::getProjectionMatrix()
{
    float fovy{ m_fovy * m_zoomFactor };
    if (fovy > 120.0f) {
        fovy = 120.0f;
        m_zoomFactor = fovy / m_fovy;
    }
    if (fovy < 1.0f) {
        fovy = 1.0f;
        m_zoomFactor = fovy / m_fovy;
    }
    glm::mat4 proj{
        glm::perspective(glm::radians(fovy), m_aspect, m_near, m_far)
    };
    return proj;
}
