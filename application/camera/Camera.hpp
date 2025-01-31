#pragma once

#include <glframework/core.h>

class Camera
{
public:  // data members
    using PosType = glm::vec3;
    using MatrixType = glm::mat4;

    PosType m_position{ 0.0f, 0.0f, 1.0f };
    PosType m_up{ 0.0f, 1.0f, 0.0f };
    PosType m_right{ 1.0f, 0.0f, 0.0f };

public:  // member functions
    Camera() = default;
    Camera(const Camera&) = default;
    Camera& operator=(const Camera&) = default;
    Camera(Camera&&) = default;
    Camera& operator=(Camera&&) = default;
    virtual ~Camera() = default;
    Camera(PosType position, PosType up, PosType right) noexcept;

    MatrixType getViewMatrix() const;
    virtual glm::mat4 getProjectionMatrix() const = 0;
};