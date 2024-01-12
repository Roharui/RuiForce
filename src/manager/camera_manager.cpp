
#include <raylib.h>

#include "core/vault.hpp"
#include "core/engine.hpp"

#include "manager/camera_manager.hpp"

void CameraManager::UpdateCameraY()
{
    if (IsKeyDown(KEY_SPACE))
    {
        Camera &camera = Vault::getCamera();
        camera.position.y += 0.3f;
        camera.target.y += 0.3f;
    }

    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        Camera &camera = Vault::getCamera();
        camera.position.y -= 0.3f;
        camera.target.y -= 0.3f;
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
    this->UpdateCameraY();
    UpdateCamera(&Vault::getCamera(), CAMERA_FIRST_PERSON);
}