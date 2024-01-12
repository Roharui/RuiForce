
#include <raylib.h>
#include <rcamera.h>

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

    Camera *camera = &Vault::getCamera();
    Vector2 mousePositionDelta = GetMouseDelta();

    bool moveInWorldPlane = true;
    bool rotateAroundTarget = false;
    bool lockView = true;
    bool rotateUp = false;

    // Mouse support
    CameraYaw(camera, -mousePositionDelta.x * CAMERA_MOUSE_MOVE_SENSITIVITY, rotateAroundTarget);
    CameraPitch(camera, -mousePositionDelta.y * CAMERA_MOUSE_MOVE_SENSITIVITY, lockView, rotateAroundTarget, rotateUp);

    // Keyboard support
    if (IsKeyDown(KEY_W))
        CameraMoveForward(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);
    if (IsKeyDown(KEY_A))
        CameraMoveRight(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
    if (IsKeyDown(KEY_S))
        CameraMoveForward(camera, -CAMERA_MOVE_SPEED, moveInWorldPlane);
    if (IsKeyDown(KEY_D))
        CameraMoveRight(camera, CAMERA_MOVE_SPEED, moveInWorldPlane);
}

void CameraManager::run()
{
    this->UpdateCameraY();
    UpdateCameraMouse();
}