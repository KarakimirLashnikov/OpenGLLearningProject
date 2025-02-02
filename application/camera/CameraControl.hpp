#pragma once
#include <unordered_map>
#include <memory>
#include "Camera.hpp"
class Shader;

inline std::unordered_map<int, bool> generateDefaultKeyMap() {
    static std::unordered_map<int, bool> default_key_map{
        {GLFW_KEY_W, false},
        {GLFW_KEY_S, false},
        {GLFW_KEY_A, false},
        {GLFW_KEY_D, false},
    };
    return default_key_map;
}

class CameraControl
{
protected:
    using Camera_Ptr = Camera*;
    using PosType = Camera::PosType;
    using MatrixType = Camera::MatrixType;

    bool m_leftMouseDown{},
        m_rightMouseDown{},
        m_middleMouseDown{};

    float m_currentX{},
        m_currentY{};

    float m_yaw{ 0.0f }, m_pitch{ 0.0f };

    float m_sensitivity{ 0.1f };
    float m_lastTime{}, m_deltaTime{};

    Camera_Ptr m_camera;
    std::unordered_map<int, bool> m_keyMap;
public:
    CameraControl(Camera_Ptr camera, const std::unordered_map<int, bool>& keyMap)
        : m_camera(camera), m_keyMap(generateDefaultKeyMap()) {
        if (!keyMap.empty()) {
            m_keyMap = keyMap;
        }
    }
    CameraControl() = default;
    virtual ~CameraControl() = default;
    CameraControl(const CameraControl&) = delete;
    CameraControl& operator=(const CameraControl&) = delete;
    CameraControl(CameraControl&&) = delete;
    CameraControl& operator=(CameraControl&&) = delete;

    virtual void onMouse(int button, int action, float x, float y) = 0;
    virtual void onCursor(float x, float y) = 0;
    virtual void onKey(int key, int action, int mods) = 0;
    virtual void onScroll(float xoffset, float yoffset) = 0;
    virtual Camera_Ptr setCamera(Camera_Ptr camera) = 0;
    virtual void setSensitivity(float sensitivity) = 0;

    void begin() {
        m_deltaTime = static_cast<float>(glfwGetTime() - m_lastTime);
        m_lastTime = static_cast<float>(glfwGetTime());
    }
};