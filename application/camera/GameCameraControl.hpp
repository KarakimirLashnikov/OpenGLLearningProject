#pragma once
#include "cameraControl.hpp"

class GameCameraControl : public CameraControl
{
public:
    GameCameraControl(Camera_Ptr camera, std::unordered_map<int, bool> keyMap = {});
    virtual ~GameCameraControl() = default;

    virtual void onMouse(int button, int action, float x, float y) override;
    virtual void onCursor(float x, float y) override;
    virtual void onKey(int key, int action, int mods) override;
    virtual void onScroll(float xoffset, float yoffset) override;
    virtual Camera_Ptr setCamera(Camera_Ptr camera) override;
    virtual void setSensitivity(float sensitivity) override;
private:
    float m_speed{ 50.0f };
    bool m_firstCursorMove{ true };
    float m_miniSample{ 0.01f };
};