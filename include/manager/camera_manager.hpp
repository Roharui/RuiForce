#pragma once

#include <raylib.h>

#include "manager/base_manager.hpp"

class CameraManager : public BaseManager
{
private:
    void UpdateCameraZ();
    void UpdateCameraKey();
    void UpdateCameraMouse();

public:
    void run() override;
};
