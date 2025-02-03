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
    if (m_leftMouseDown) {
        float xoffset = x - m_currentX;
        float yoffset = m_currentY - y;
        m_currentX = x;
        m_currentY = y;
        if (m_firstCursorMove) {
            m_firstCursorMove = false;
            return;
        }
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
        front.z = -cos(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
        front.y = sin(glm::radians(this->m_pitch));
        front.x = sin(glm::radians(this->m_yaw)) * cos(glm::radians(this->m_pitch));
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
        this->m_keyMap[key] = true;
        switch (int left{ 1 }, right{ -1 }, back{ -1 }, forward{ 1 }; key) {
        case GLFW_KEY_A:
            if (m_keyMap[GLFW_KEY_D]) goto EXIT_POINT;
            left_right_move(left);
            break;
        case GLFW_KEY_D:
            if (m_keyMap[GLFW_KEY_A]) goto EXIT_POINT;
            left_right_move(right);
            break;
        case GLFW_KEY_W:
            if (m_keyMap[GLFW_KEY_S]) goto EXIT_POINT;
            forward_backward_move(forward);
            break;
        case GLFW_KEY_S:
            if (m_keyMap[GLFW_KEY_W]) goto EXIT_POINT;
            forward_backward_move(back);
            break;
        default:
            goto EXIT_POINT;
        }
    }

    if (action == GLFW_RELEASE && this->m_keyMap.find(key) != this->m_keyMap.end()) {
        this->m_keyMap[key] = false;
    }

EXIT_POINT:
    return;
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
