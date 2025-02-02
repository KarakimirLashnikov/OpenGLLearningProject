#pragma once

#include "Camera.hpp"

class PerspectiveCamera : public Camera
{
public:  // data members
    float m_fovy{};  // vertical field of view in degrees
    float m_aspect{};  // aspect ratio (width/height)
    float m_near{};
    float m_far{};

public:  // methods
    PerspectiveCamera() = default;
    virtual ~PerspectiveCamera() = default;
    PerspectiveCamera(const PerspectiveCamera&) = default;
    PerspectiveCamera& operator=(const PerspectiveCamera&) = default;
    PerspectiveCamera(PerspectiveCamera&&) = default;
    PerspectiveCamera& operator=(PerspectiveCamera&&) = default;

    PerspectiveCamera(float fovy, float aspect, float near, float far,
        PosType position, PosType up, PosType front);
    PerspectiveCamera(float fovy, float aspect, float near, float far);

    glm::mat4 getProjectionMatrix()override final;
};