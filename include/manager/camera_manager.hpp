#pragma once

#include "manager/base_manager.hpp"

#define CAMERA_MOVE_SPEED 0.09f
#define CAMERA_ROTATION_SPEED 0.03f
#define CAMERA_PAN_SPEED 0.2f

#define CAMERA_MOUSE_MOVE_SENSITIVITY 0.003f
#define CAMERA_MOUSE_SCROLL_SENSITIVITY 1.5f

class CameraManager : public BaseManager
{
private:
    void UpdateCameraY();
    void UpdateCameraMouse();

public:
    void run() override;
};
