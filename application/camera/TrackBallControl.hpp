#pragma once
#include "CameraControl.hpp"
class Shader;

class TrackBallControl : public CameraControl
{
public:
    TrackBallControl(Camera_Ptr camera);
    virtual ~TrackBallControl() = default;

    virtual void onMouse(int button, int action, double x, double y) override;
    virtual void onCursor(double x, double y) override;
    virtual void onKey(int key, int action, int mods) override;
    virtual void setCamera(Camera_Ptr camera) override;
    virtual void setSensitivity(float sensitivity) override;
    virtual void update(Shader*);
    virtual void pitch(float angle) override;
    virtual void yaw(float angle) override;
};