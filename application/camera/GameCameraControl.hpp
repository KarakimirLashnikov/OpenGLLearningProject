#pragma once
#include "cameraControl.hpp"

class GameCameraControl : public CameraControl
{
public:
    GameCameraControl(Camera_Ptr camera);
    virtual ~GameCameraControl() = default;

    virtual void onMouse(int button, int action, double x, double y) override;
    virtual void onCursor(double x, double y) override;
    virtual void onKey(int key, int action, int mods) override;
    virtual void setCamera(Camera_Ptr camera) override;
    virtual void setSensitivity(float sensitivity) override;
    virtual void update(Shader*) override;
    virtual void pitch(float angle) override;
    virtual void yaw(float angle) override;
private:
    float m_speed{};
};