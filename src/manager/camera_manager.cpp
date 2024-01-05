
#include <raylib.h>

#include "core/vault.hpp"
#include "manager/camera_manager.hpp"

void UpdateCameraZ()
{
    float scroll = GetMouseWheelMove();
    Vault::instance().camera.position.z += scroll;
}

void UpdateCameraXY()
{
    Camera &camera = Vault::instance().camera;
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