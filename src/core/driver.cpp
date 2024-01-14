
#include <raylib.h>

#include <iostream>
#include <string>

#include "config.hpp"

#include "core/driver.hpp"
#include "core/vault.hpp"
#include "core/engine.hpp"

#include "scenario/goal_scenario.hpp"

Driver::Driver()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    SetTargetFPS(FPS);

    Vault::instance();
    Engine::instance();
    Engine::instance().initialize(new GoalScenario());
}

void Driver::Run()
{
    while (!WindowShouldClose())
    {
        this->Update();
        this->Draw();
    }

    CloseWindow();
}

void Driver::Update()
{
    Engine::instance().run();
}

void Driver::Draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    Vault::instance().draw3D();
    Vault::instance().draw2D();

    EndDrawing();
}