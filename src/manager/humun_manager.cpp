
#include <ctime>
#include <format>

#include <raylib.h>
#include <raymath.h>

#include "core/vault.hpp"
#include "core/engine.hpp"

#include "manager/humun_manager.hpp"
#include "object/humun_object.hpp"

using namespace std;

int select = 0;

void HumunMananger::MoveToward()
{
    HumunObject *humun = (HumunObject *)Vault::getObject().at(select);
    if (IsKeyDown(KEY_I))
    {
        humun->action = KEY_I;
        humun->goFrame = FPS;
    }
    if (IsKeyDown(KEY_K))
    {
        humun->action = KEY_K;
        humun->goFrame = FPS;
    }

    if (humun->goFrame == 0)
    {
        return;
    }

    if (humun->action == KEY_I)
    {
        humun->loc = Vector3Add(humun->loc, Vector3RotateByAxisAngle({0.1, 0., 0.}, {0., 1., 0.}, humun->angle));
    }
    if (humun->action == KEY_K)
    {
        humun->loc = Vector3Subtract(humun->loc, Vector3RotateByAxisAngle({0.1, 0., 0.}, {0., 1., 0.}, humun->angle));
    }

    humun->goFrame--;

    float MAP_SIZE_MIN = -(MAP_SIZE / 2 - HUMUN_SIZE_R);
    float MAP_SIZE_MAX = (MAP_SIZE / 2 - HUMUN_SIZE_R);

    humun->loc = Vector3Min(humun->loc, {MAP_SIZE_MAX, 99., MAP_SIZE_MAX});
    humun->loc = Vector3Max(humun->loc, {MAP_SIZE_MIN, 00., MAP_SIZE_MIN});
}

void HumunMananger::MoveAngle()
{
    HumunObject *humun = (HumunObject *)Vault::getObject().at(select);

    if (IsKeyDown(KEY_J))
    {
        humun->angle += 0.1f;
    }
    if (IsKeyDown(KEY_L))
    {
        humun->angle -= 0.1f;
    }
}

void HumunMananger::SelectHumun()
{
    if (IsKeyDown(KEY_TAB))
    {
        select += 1;
        select %= Vault::getObject().size();

        for (BaseObject *humun : Vault::getObject())
        {
            ((HumunObject *)humun)->selected = false;
        }

        ((HumunObject *)Vault::getObject().at(select))->selected = true;
    }
}

void HumunMananger::Capture()
{
    if (IsKeyPressed(KEY_P))
    {
        HumunObject *humun = (HumunObject *)Vault::getObject().at(select);

        BeginDrawing();

        RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

        BeginTextureMode(target);
        ClearBackground(RAYWHITE);

        BeginMode3D({humun->loc,                                                                             // Camera position
                     Vector3Add(humun->loc, Vector3RotateByAxisAngle({3.0, 0, 0}, {0, 1, 0}, humun->angle)), // Camera looking at point
                     Vector3{0.0f, 1.0f, 0.0f},                                                              // Camera up vector (rotation towards target)
                     45.0f,                                                                                  // Camera field-of-view Y
                     CAMERA_PERSPECTIVE});

        Vault::getMap().draw3D();

        for (int i = 0; i < Vault::getObject().size(); i++)
        {
            if (i == select)
                continue;

            Vault::getObject().at(i)->draw3D();
        }

        EndMode3D();

        EndTextureMode();

        Image image = LoadImageFromTexture(target.texture);
        ImageFlipVertical(&image);
        ExportImage(image, std::format("{}.png", time(0)).c_str());
        UnloadImage(image);

        UnloadRenderTexture(target);
    }
}

void HumunMananger::run()
{
    this->SelectHumun();
    this->MoveToward();
    this->MoveAngle();
    this->Capture();
}