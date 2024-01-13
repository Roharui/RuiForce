
#include <ctime>
#include <format>
#include <thread>

#include <raylib.h>
#include <raymath.h>

#include "config.hpp"

#include "core/vault.hpp"

#include "utils/random.hpp"
#include "utils/strdup.hpp"

#include "object/humun_object.hpp"

#include "manager/rutine_manager.hpp"

#include "service/mq_service.hpp"

using namespace std;

float MAP_SIZE_MIN = -(MAP_SIZE / 2 - HUMUN_SIZE_R);
float MAP_SIZE_MAX = (MAP_SIZE / 2 - HUMUN_SIZE_R);

void RutineManager::randomInitialze()
{
    Vault::humun->loc = {
        getRandf(MAP_SIZE_MIN, MAP_SIZE_MAX),
        HUMUN_SIZE_R,
        getRandf(MAP_SIZE_MIN, MAP_SIZE_MAX),
    };
    Vault::humun->angle = getRandf(0, 6);

    Vault::goal->loc = {
        getRandf(MAP_SIZE_MIN, MAP_SIZE_MAX),
        HUMUN_SIZE_R,
        getRandf(MAP_SIZE_MIN, MAP_SIZE_MAX),
    };
}

void RutineManager::Capture()
{
    HumunObject *humun = (HumunObject *)Vault::getObject().at(0);

    BeginDrawing();

    RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    BeginTextureMode(target);
    ClearBackground(RAYWHITE);

    BeginMode3D({humun->loc,
                 Vector3Add(humun->loc, Vector3RotateByAxisAngle({3.0, 0., 0.}, {0., 1., 0.}, humun->angle)),
                 Vector3{0.0f, 1.0f, 0.0f},
                 45.0f,
                 CAMERA_PERSPECTIVE});

    Vault::getMap().draw3D();

    for (BaseObject *basOobj : Vault::getObject())
    {
        if (basOobj == humun)
            continue;

        ((HumunObject *)basOobj)->draw3D();
    }

    EndMode3D();

    EndTextureMode();

    this->fileName = std::format("{}.png", time(0));

    Image image = LoadImageFromTexture(target.texture);
    ImageFlipVertical(&image);

    ExportImage(image, this->fileName.c_str());

    UnloadImage(image);
    UnloadRenderTexture(target);
}

void RutineManager::mqProduce()
{
    thread t(&this->mqService.sendMessage, this->mqService, this->fileName.c_str(), this->fileName.size());
    t.detach();
}

void RutineManager::waitForResponse()
{
    if (this->mqService.isResponsed())
    {
        this->step++;
    }
}

void RutineManager::run()
{
    if (IsKeyPressed(KEY_P))
    {
        this->step = 0;
        this->turn = DEFAULT_TURN;
        this->phase = DEFAULT_PHASE;
    }

    if (this->phase > 0)
    {
        switch (this->step)
        {
        case 0:
            this->randomInitialze();
            this->step++;
            break;

        case 1:
            this->Capture();
            this->step++;
            break;

        case 2:
            this->mqProduce();
            this->step++;
            break;

        case 3:
            this->waitForResponse();
            break;

        default:
            break;
        }
    }
}