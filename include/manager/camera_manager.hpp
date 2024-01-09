#pragma once

#include "manager/base_manager.hpp"

class CameraManager : public BaseManager
{
private:
    void UpdateCameraY();
    void UpdateCameraMouse();

public:
    void run() override;
};
