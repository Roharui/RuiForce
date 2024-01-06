
#include <raylib.h>

#include <iostream>
#include <string>

#include "config.hpp"

#include "core/driver.hpp"
#include "core/vault.hpp"
#include "core/engine.hpp"

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

    Engine::initialize();
}

void Driver::Update()
{
    Engine::run();
    Engine::tictok();
}

void Driver::Drow()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(Vault::getCamera());

    DrawCube(Vector3{0.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 0.0f, RED);
    DrawCubeWires(Vector3{0.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 0.0f, MAROON);

    EndMode3D();

    DrawText(std::to_string(Engine::getWait()).c_str(), 0, 0, 10, BLACK);

    EndDrawing();
}