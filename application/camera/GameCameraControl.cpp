#include "GameCameraControl.hpp"

GameCameraControl::GameCameraControl(Camera_Ptr camera)
    : CameraControl(std::move(camera), {})
{
}

void GameCameraControl::onKey(int key, int action, int mods)
{
    m_keyMap[key] = action;

    // w / s to move forward / backward, a / d to strafe left / right
    switch (key)
    {
    case GLFW_KEY_W:
        break;
    case GLFW_KEY_S:
        break;
    case GLFW_KEY_A:
        break;
    case GLFW_KEY_D:
        break;
    default:
        break;
    }
}
