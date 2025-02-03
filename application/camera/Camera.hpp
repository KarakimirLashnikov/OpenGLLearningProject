#pragma once

#include <glframework/core.h>

class Camera
{
public:  // data members
    using PosType = glm::vec3;
    using MatrixType = glm::mat4;

    PosType m_position{ 0.0f, 0.0f, 5.0f };
    PosType m_up{ 0.0f, 1.0f, 0.0f };
    PosType m_front{ 0.0f, 0.0f, -1.0f };
    float m_zoomFactor{ 1.0f };  // 45 degrees FOV by default

public:  // member functions
    Camera() = default;
    Camera(const Camera&) = default;
    Camera& operator=(const Camera&) = default;
    Camera(Camera&&) = default;
    Camera& operator=(Camera&&) = default;
    virtual ~Camera() = default;
    Camera(PosType position, PosType up, PosType front) noexcept;

    MatrixType getViewMatrix() const;
    PosType getPosition() const noexcept;
    virtual MatrixType getProjectionMatrix() = 0;
};