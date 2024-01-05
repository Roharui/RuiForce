
#include <raylib.h>

#include "config.hpp"

#include "core/driver.hpp"
#include "core/vault.hpp"

#include "manager/camera_manager.hpp"

Driver::Driver()
{
    Initialize();
}

void Driver::Run()
{
    while (!WindowShouldClose())
    {
        this->Update();
        this->Drow();
    }

    CloseWindow();
}

void Driver::Initialize()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    DisableCursor();

    SetTargetFPS(FPS);
}

void Driver::Update()
{
    UpdateCameraXY();
    UpdateCameraZ();
}

void Driver::Drow()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(Vault::instance().camera);

    DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 0.0f, RED);
    DrawCubeWires(Vector3{0.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 0.0f, MAROON);

    EndMode3D();

    EndDrawing();
}