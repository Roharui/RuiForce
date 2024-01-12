
#include <ctime>
#include <format>
#include <random>

#include <raylib.h>
#include <raymath.h>

#include "config.hpp"

#include "core/vault.hpp"

#include "object/humun_object.hpp"

#include "manager/rutine_manager.hpp"

using namespace std;

void RutineManager::Capture()
{
    BeginDrawing();

    RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    BeginTextureMode(target);
    ClearBackground(RAYWHITE);

    BeginMode3D({this->humun->loc,
                 Vector3Add(this->humun->loc, Vector3RotateByAxisAngle({3.0, 0., 0.}, {0., 1., 0.}, this->humun->angle)),
                 Vector3{0.0f, 1.0f, 0.0f},
                 45.0f,
                 CAMERA_PERSPECTIVE});

    Vault::getMap().draw3D();

    for (BaseObject *basOobj : Vault::getObject())
    {
        if (basOobj == this->humun)
            continue;

        ((HumunObject *)basOobj)->draw3D();
    }

    EndMode3D();

    EndTextureMode();

    Image image = LoadImageFromTexture(target.texture);
    ImageFlipVertical(&image);
    ExportImage(image, std::format("{}.png", time(0)).c_str());
    UnloadImage(image);

    UnloadRenderTexture(target);
}

void RutineManager::run()
{
    if (IsKeyPressed(KEY_P))
    {
        this->step = 0;
        this->turn = DEFAULT_TURN;
        this->phase = DEFAULT_PHASE;
        this->humun = (HumunObject *)Vault::getObject().at(0);
    }

    if (this->phase > 0)
    {
        // this->MoveHumun();
    }
}