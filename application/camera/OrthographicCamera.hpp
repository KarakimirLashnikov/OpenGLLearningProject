#pragma once

#include "Camera.hpp"

class OrthographicCamera : public Camera
{
private:  // data members
    float m_left_ms{};
    float m_right_ms{};
    float m_top_ms{};
    float m_bottom_ms{};
    float m_near_ms{};
    float m_far_ms{};

public:
    OrthographicCamera() = default;
    OrthographicCamera(const OrthographicCamera&) = default;
    OrthographicCamera& operator=(const OrthographicCamera&) = default;
    OrthographicCamera(OrthographicCamera&&) = default;
    OrthographicCamera& operator=(OrthographicCamera&&) = default;
    virtual ~OrthographicCamera() = default;

    OrthographicCamera(float left, float right, float top,
        float bottom, float near, float far) noexcept;

    glm::mat4 getProjectionMatrix() const override final;
};