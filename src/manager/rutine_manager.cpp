
#include <iostream>
#include <ctime>
#include <format>
#include <thread>

#include <raylib.h>
#include <raymath.h>

#include "config.hpp"

#include "core/vault.hpp"

#include "utils/random.hpp"
#include "utils/file.hpp"
#include "utils/collision.hpp"

#include "object/humun_object.hpp"

#include "manager/rutine_manager.hpp"

#include "service/mq_service.hpp"
#include "service/move_service.hpp"

using namespace std;

float MAP_SIZE_MIN = -(MAP_SIZE / 2 - HUMUN_SIZE_R);
float MAP_SIZE_MAX = (MAP_SIZE / 2 - HUMUN_SIZE_R);

void RutineManager::initialze()
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

    this->moveBefore = 0.;
    this->moveAfter = 0.;

    this->inGoal = false;
}

void RutineManager::Capture()
{
    HumunObject *humun = Vault::humun;

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

    this->fileName = std::format("{}\\{}.png", ExePath(), time(0));

    Image image = LoadImageFromTexture(target.texture);
    ImageFlipVertical(&image);

    // ExportImage(image, this->fileName.c_str());

    UnloadImage(image);
    UnloadRenderTexture(target);
}

void RutineManager::mqProduceChoose()
{
    thread t(&MQService::sendMessage, this->mqService, this->fileName.c_str());
    t.detach();
}

void RutineManager::waitForResponse()
{
    if (!this->mqService->dataQueue.empty())
    {
        this->angle = this->mqService->dataQueue.at(0);
        this->mqService->dataQueue.pop_front();
        this->frame = 0;
        this->step++;
    }
}

void RutineManager::changeAngle()
{
    this->frame++;
    HumunObject *humun = Vault::humun;

    humun->angle += (this->angle / 30);

    if (this->frame == 30)
    {
        this->frame = 0;
        this->step++;
    }
}

void RutineManager::movePosition()
{
    HumunObject *humun = Vault::humun;
    GoalObject *goal = Vault::goal;

    if (this->frame == 0)
    {
        this->moveBefore = Vector3DistanceSqr(humun->loc, goal->loc);
    }

    if (CheckCollisionBoxesV(humun->loc, humun->size, goal->loc, goal->size))
    {
        this->inGoal = true;
        this->frame = 0;
        this->step++;
        return;
    }

    this->frame++;

    humun->loc = MoveToward(humun->loc, 1, humun->angle);

    if (this->frame == FPS)
    {
        this->frame = 0;
        this->moveAfter = Vector3DistanceSqr(humun->loc, goal->loc);
        this->moveAmount = to_string(this->moveBefore - this->moveAfter);
        this->step++;
    }
}

void RutineManager::mqProduceResult()
{
    thread t(&MQService::sendMessage, this->mqService, this->moveAmount.c_str());
    t.detach();
}

void RutineManager::run()
{
    if (IsKeyPressed(KEY_P))
    {
        delete this->mqService;
        this->step = 0;
        this->turn = DEFAULT_TURN;
        this->phase = DEFAULT_PHASE;
        this->mqService = new MQService();
    }

    if (this->phase > 0)
    {
        switch (this->step)
        {
        case 0:
            this->initialze();
            this->step++;
            break;

        case 1:
            this->Capture();
            this->step++;
            break;

        case 2:
            this->mqProduceChoose();
            this->step++;
            break;

        case 3:
            this->waitForResponse();
            break;

        case 4:
            this->changeAngle();
            break;

        case 5:
            this->movePosition();
            break;

        case 6:
            this->mqProduceResult();
            this->step++;
            break;

        case 7:
            this->turn--;
            this->step = 1;
            if (this->turn == 0 || this->inGoal)
            {
                this->step = 0;
                this->phase--;
            }
            break;

        default:
            break;
        }
    }
}