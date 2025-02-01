#include "TrackBallControl.hpp"
#include "glframework/shader.hpp"

TrackBallControl::TrackBallControl(Camera_Ptr camera)
    : CameraControl(std::move(camera), {})
{
}

void TrackBallControl::onMouse(int button, int action, double x, double y)
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

void TrackBallControl::onCursor(double x, double y)
{
    //this->m_camera->m_position.z -= (y * this->m_senesitivity);
    if (this->m_leftMouseDown)
    {
        double dx = x - this->m_currentX;
        double dy = y - this->m_currentY;
        this->m_currentX = x;
        this->m_currentY = y;
        this->pitch(dy);
        this->yaw(dx);
    }
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
    float rat = angle * this->m_senesitivity;
    glm::vec3 cur{ 0.0f, rat , rat };
    this->m_camera->m_up += cur;
}

void TrackBallControl::yaw(float angle)
{
    //this->m_camera->m_right -= angle * this->m_senesitivity;
}
