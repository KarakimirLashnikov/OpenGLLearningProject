#include "OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(
    float left, float right, float top, float bottom, float, float) noexcept
    : m_left_ms(left), m_right_ms(right), m_top_ms(top),
    m_bottom_ms(bottom), m_near_ms(0.0f), m_far_ms(1.0f)
{
}

OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom, float, float, PosType pos, PosType up, PosType front) noexcept
    : m_left_ms(left), m_right_ms(right), m_top_ms(top),
    m_bottom_ms(bottom), m_near_ms(0.0f), m_far_ms(1.0f),
    Camera(pos, up, front)
{
}


glm::mat4 OrthographicCamera::getProjectionMatrix()
{
    glm::mat4 ortho{
        glm::ortho(m_left_ms, m_right_ms, m_top_ms, m_bottom_ms, m_near_ms, m_far_ms)
    };
    return ortho;
}
