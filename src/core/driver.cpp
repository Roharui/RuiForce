
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
        this->draw();
    }

    CloseWindow();
}

void Driver::Initialize()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    DisableCursor();

    SetTargetFPS(FPS);

    Vault::initialize();
    Engine::initialize();
}

void Driver::Update()
{
    Engine::run();
    Engine::tictok();
}

void Driver::draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    BeginMode3D(Vault::getCamera());

    Vault::getMap().draw();

    EndMode3D();

    EndDrawing();
}