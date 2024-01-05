#pragma once

#include <raylib.h>

#include "manager/base_manager.hpp"

class CameraManager : public BaseManager
{
private:
    void UpdateCameraXY();
    void UpdateCameraZ();

public:
    void run() override;
};
