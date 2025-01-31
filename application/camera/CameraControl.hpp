#pragma once
#include <unordered_map>
#include <memory>
#include "Camera.hpp"
class Shader;

class CameraControl
{
protected:
    using Camera_Ptr = Camera*;
    bool m_leftMouseDown{},
        m_rightMouseDown{},
        m_middleMouseDown{};

    double m_currentX{},
        m_currentY{};

    float m_senesitivity{ 0.02f };

    Camera_Ptr m_camera;
    std::unordered_map<int, bool> m_keyMap;
public:
    CameraControl(Camera_Ptr camera, const std::unordered_map<int, bool>& keyMap)
        : m_camera(std::move(camera)), m_keyMap(keyMap) {
    }
    CameraControl() = default;
    virtual ~CameraControl() = default;
    CameraControl(const CameraControl&) = delete;
    CameraControl& operator=(const CameraControl&) = delete;
    CameraControl(CameraControl&&) = delete;
    CameraControl& operator=(CameraControl&&) = delete;

    virtual void onMouse(int button, int action, double x, double y) = 0;
    virtual void onCursor(double x, double y) = 0;
    virtual void onKey(int key, int action, int mods) = 0;
    virtual void setCamera(Camera_Ptr camera) = 0;
    virtual void setSensitivity(float sensitivity) = 0;
    virtual void update(Shader*) = 0;
    virtual void pitch(float angle) = 0;
    virtual void yaw(float angle) = 0;
};