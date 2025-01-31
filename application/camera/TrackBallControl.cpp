#include "TrackBallControl.hpp"
#include "glframework/shader.hpp"

TrackBallControl::TrackBallControl(Camera_Ptr camera)
    : CameraControl(std::move(camera), {})
{
}

void TrackBallControl::onMouse(int button, int action, double x, double y)
{
}

void TrackBallControl::onCursor(double x, double y)
{
    this->m_camera->m_position.z -= (y * this->m_senesitivity);
}

void TrackBallControl::onKey(int key, int action, int mods)
{
}

void TrackBallControl::setCamera(Camera_Ptr camera)
{
}

void TrackBallControl::setSensitivity(float sensitivity)
{
    this->m_senesitivity = sensitivity;
}

void TrackBallControl::update(Shader* shader)
{
}

void TrackBallControl::pitch(float angle)
{
    this->m_camera->m_up += angle * this->m_senesitivity;
}

void TrackBallControl::yaw(float angle)
{
    this->m_camera->m_right += angle * this->m_senesitivity;
}
