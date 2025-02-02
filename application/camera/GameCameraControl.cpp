#include "GameCameraControl.hpp"
#include <iostream>

GameCameraControl::GameCameraControl(Camera_Ptr camera, std::unordered_map<int, bool> keyMap)
    : CameraControl(camera, keyMap)
{
}

void GameCameraControl::onMouse(int button, int action, float x, float y)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        m_leftMouseDown = true;
        return;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        m_leftMouseDown = false;
        m_firstCursorMove = true;
        return;
    }
}

void GameCameraControl::onCursor(float x, float y)
{
    if (m_firstCursorMove) {
        m_currentX = x;
        m_currentY = y;
        m_firstCursorMove = false;
        return;
    }
    if (m_leftMouseDown) {
        float xoffset = x - m_currentX;
        float yoffset = m_currentY - y;
        m_currentX = x;
        m_currentY = y;
        xoffset *= this->m_sensitivity;
        yoffset *= this->m_sensitivity;
        this->m_yaw += xoffset;
        this->m_pitch += yoffset;
        if (this->m_pitch > 89.0f) {
            this->m_pitch = 89.0f;
        }
        if (this->m_pitch < -89.0f) {
            this->m_pitch = -89.0f;
        }
        glm::vec3 front{};
        front.x = cos(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
        front.y = sin(glm::radians(this->m_pitch));
        front.z = sin(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
        std::cout << glm::to_string(front) << std::endl;
        this->m_camera->m_front = glm::normalize(front);
    }
}

void GameCameraControl::onKey(int key, int action, int mods)
{
    auto left_right_move{
    [=](int dir) -> void {
        float speed = m_speed * dir * m_deltaTime;
        m_camera->m_position += glm::cross(m_camera->m_up, m_camera->m_front) * speed; }
    };

    auto forward_backward_move{
        [=](int dir) -> void {
            float speed = m_speed * dir * m_deltaTime;
            m_camera->m_position += m_camera->m_front * speed; }
    };

    if (this->m_keyMap.find(key) != this->m_keyMap.end() &&
        (action == GLFW_PRESS || action == GLFW_REPEAT)) {
        switch (int left{ 1 }, right{ -1 }, back{ -1 }, forward{ 1 }; key) {
        case GLFW_KEY_A:
            left_right_move(left);
            break;
        case GLFW_KEY_D:
            left_right_move(right);
            break;
        case GLFW_KEY_W:
            forward_backward_move(forward);
            break;
        case GLFW_KEY_S:
            forward_backward_move(back);
            break;
        default:
            break;
        }
    }
}

void GameCameraControl::onScroll(float xoffset, float yoffset)
{
    if (yoffset > 0) {
        this->m_camera->m_zoomFactor -= 0.1f;
    }
    else if (yoffset < 0) {
        this->m_camera->m_zoomFactor += 0.1f;
    }
}

CameraControl::Camera_Ptr GameCameraControl::setCamera(Camera_Ptr camera)
{
    Camera_Ptr oldCamera = this->m_camera;
    this->m_camera = camera;
    return oldCamera;
}

void GameCameraControl::setSensitivity(float sensitivity)
{
    this->m_sensitivity = sensitivity;
}
