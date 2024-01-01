
#include <raylib.h>

#include "config.hpp"

#include "driver.hpp"

#include "camera_manager.hpp"

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
    // Define the camera to look into our 3d world
    this->camera = {0};
    this->camera.position = (Vector3){00.0f, 0.0f, 10.0f}; // Camera position
    this->camera.target = (Vector3){0.0f, 0.0f, 0.0f};     // Camera looking at point
    this->camera.up = (Vector3){0.0f, 1.0f, 0.0f};         // Camera up vector (rotation towards target)
    this->camera.fovy = 45.0f;                             // Camera field-of-view Y
    this->camera.projection = CAMERA_PERSPECTIVE;          // Camera projection type

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    DisableCursor();

    SetTargetFPS(FPS);
}

void Driver::Update()
{
    UpdateCameraXY(this->camera);
    UpdateCameraZ(this->camera);
}

void Driver::Drow()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(this->camera);

    DrawCube((Vector3){0.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 0.0f, RED);
    DrawCubeWires((Vector3){0.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 0.0f, MAROON);

    EndMode3D();

    EndDrawing();
}