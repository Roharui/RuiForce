
#include <raylib.h>

#include "core/vault.hpp"
#include "core/engine.hpp"

#include "manager/camera_manager.hpp"

void CameraManager::UpdateCameraZ()
{
    float scroll = GetMouseWheelMove();
    Vault::getCamera().position.z += scroll;
}

void CameraManager::UpdateCameraKey()
{
    Camera &camera = Vault::getCamera();
    if (IsKeyDown(KEY_DOWN))
    {
        camera.position.y -= 0.5;
        camera.target.y -= 0.5;
    }
    if (IsKeyDown(KEY_UP))
    {
        camera.position.y += 0.5;
        camera.target.y += 0.5;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        camera.position.x += 0.5;
        camera.target.x += 0.5;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        camera.position.x -= 0.5;
        camera.target.x -= 0.5;
    }
}

void CameraManager::UpdateCameraMouse()
{
    Camera &camera = Vault::getCamera();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 delta = GetMouseDelta();
        camera.position.x -= delta.x / (0.8f * camera.position.z);
        camera.position.y += delta.y / (0.8f * camera.position.z);

        camera.target.x -= delta.x / (0.8f * camera.position.z);
        camera.target.y += delta.y / (0.8f * camera.position.z);
    }
}

void CameraManager::run()
{
    this->UpdateCameraZ();
    this->UpdateCameraKey();
    this->UpdateCameraMouse();
}