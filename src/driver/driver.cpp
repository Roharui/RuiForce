
#include <raylib.h>

#include "config.hpp"

#include "driver.hpp"

Driver::Driver()
{
    initialize();
}

void Driver::run()
{
    while (!WindowShouldClose())
    {
        this->drow();
    }

    CloseWindow();
}

void Driver::initialize()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);

    SetTargetFPS(FPS);
}

void Driver::drow()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
}