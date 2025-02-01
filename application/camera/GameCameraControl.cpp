#include "GameCameraControl.hpp"
#include <iostream>
inline constexpr float PI{ 3.14159265359f };

GameCameraControl::GameCameraControl(Camera_Ptr camera)
    : CameraControl(std::move(camera), {})
{
}

void GameCameraControl::onMouse(int button, int action, double x, double y)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_RELEASE) {
            this->m_leftMouseDown = false;
            return;
        }
        else if (action == GLFW_PRESS) {
            this->m_leftMouseDown = true;
            this->m_currentX = x;
            this->m_currentY = y;
            return;
        }
    }

    if (this->m_leftMouseDown)
    {
        float dx = (x - this->m_currentX) * this->m_senesitivity * (1.0f / this->m_zoomFactor);
        float dy = (y - this->m_currentY) * this->m_senesitivity * (1.0f / this->m_zoomFactor);
        float angleY = dy * 180.0f / PI;
        float angleX = -(dx * 180.0f / PI);
        this->m_currentX = x;
        this->m_currentY = y;
        this->pitch(angleY);
        this->yaw(angleX);
    }
}

void GameCameraControl::onCursor(double x, double y)
{
    if (y > 0) {
        this->m_zoomFactor += 0.01f;
        this->m_camera->m_position.z -= 0.01f;
    }
    else {
        this->m_zoomFactor -= 0.01f;
        this->m_camera->m_position.z += 0.01f;
    }
}

void GameCameraControl::onKey(int key, int action, int mods)
{
    float x_dir{}, z_dir{};
    switch (key)
    {
    case GLFW_KEY_W:
        this->m_keyMap[GLFW_KEY_W] = (action == GLFW_PRESS ? true : false);
        z_dir = -3.0f * this->m_senesitivity * (1.0f / this->m_zoomFactor);
        if (this->m_keyMap[GLFW_KEY_S])
            z_dir = 0;
        this->m_camera->m_position.z += z_dir;
        break;
    case GLFW_KEY_S:
        this->m_keyMap[GLFW_KEY_S] = (action == GLFW_PRESS ? true : false);
        z_dir = 3.0f * this->m_senesitivity * (1.0f / this->m_zoomFactor);
        if (this->m_keyMap[GLFW_KEY_W])
            z_dir = 0;
        this->m_camera->m_position.z += z_dir;
        break;
    case GLFW_KEY_A:
        this->m_keyMap[GLFW_KEY_A] = (action == GLFW_PRESS ? true : false);
        x_dir = -3.0f * this->m_senesitivity * (1.0f / this->m_zoomFactor);
        if (this->m_keyMap[GLFW_KEY_D])
            x_dir = 0;
        this->m_camera->m_position.x += x_dir;
        break;
    case GLFW_KEY_D:
        this->m_keyMap[GLFW_KEY_D] = (action == GLFW_PRESS ? true : false);
        x_dir = 3.0f * this->m_senesitivity * (1.0f / this->m_zoomFactor);
        if (this->m_keyMap[GLFW_KEY_A])
            x_dir = 0;
        this->m_camera->m_position.x += x_dir;
        break;
    default:
        std::cout << "unsupported key: " << key << std::endl;
        break;
    }
}

void GameCameraControl::setCamera(Camera_Ptr camera)
{
    this->m_camera = camera;
}

void GameCameraControl::setSensitivity(float sensitivity)
{
    this->m_senesitivity = sensitivity;
}

void GameCameraControl::update(Shader*)
{
}

void GameCameraControl::pitch(float angle)
{
    glm::vec3 pos{ 0.0f, std::cos(angle), angle };
    this->m_camera->m_up += pos;
}

void GameCameraControl::yaw(float angle)
{
    glm::vec3 pos{ std::cos(angle), 0.0f, angle };
    this->m_camera->m_right += pos;
}
