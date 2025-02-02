#include "TrackBallControl.hpp"
#include "glframework/shader.hpp"

TrackBallControl::TrackBallControl(Camera_Ptr camera)
    : CameraControl(std::move(camera), {})
{
}

void TrackBallControl::onMouse(int button, int action, float x, float y)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        this->m_currentX = x;
        this->m_currentY = y;
        this->m_leftMouseDown = true;
        return;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        this->m_leftMouseDown = false;
    }
}

void TrackBallControl::onCursor(float x, float y)
{
}

void TrackBallControl::onKey(int key, int action, int mods)
{
}

CameraControl::Camera_Ptr TrackBallControl::setCamera(Camera_Ptr camera)
{
    return this->m_camera;
}

void TrackBallControl::setSensitivity(float sensitivity)
{
    this->m_sensitivity = sensitivity;
}
