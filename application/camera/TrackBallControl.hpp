#pragma once
#include "CameraControl.hpp"
class Shader;

class TrackBallControl : public CameraControl
{
public:
    TrackBallControl(Camera_Ptr camera);
    virtual ~TrackBallControl() = default;

    virtual void onMouse(int button, int action, float x, float y) override;
    virtual void onCursor(float x, float y) override;
    virtual void onKey(int key, int action, int mods) override;
    virtual Camera_Ptr setCamera(Camera_Ptr camera) override;
    virtual void setSensitivity(float sensitivity) override;
};