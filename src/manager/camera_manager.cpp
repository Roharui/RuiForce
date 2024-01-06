
#include <raylib.h>

#include "core/vault.hpp"
#include "core/engine.hpp"

#include "manager/camera_manager.hpp"

void CameraManager::UpdateCameraZ()
{
    float scroll = GetMouseWheelMove();
    Vault::getCamera().position.z += scroll;
}

void CameraManager::UpdateCameraXY()
{
    Camera &camera = Vault::getCamera();
    if (IsKeyDown(KEY_DOWN))
    {
        camera.position.y -= 0.1;
        camera.target.y -= 0.1;
    }
    if (IsKeyDown(KEY_UP))
    {
        camera.position.y += 0.1;
        camera.target.y += 0.1;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        camera.position.x += 0.1;
        camera.target.x += 0.1;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        camera.position.x -= 0.1;
        camera.target.x -= 0.1;
    }
}

void CameraManager::run()
{
    this->UpdateCameraZ();
    this->UpdateCameraXY();
}