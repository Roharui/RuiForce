
#include <iostream>
#include <ctime>
#include <format>
#include <thread>

#include <raylib.h>
#include <raymath.h>

#include <nlohmann/json.hpp>

#include "config.hpp"

#include "core/vault.hpp"

#include "utils/random.hpp"
#include "utils/file.hpp"
#include "utils/collision.hpp"

#include "object/humun_object.hpp"

#include "service/mq_service.hpp"
#include "service/move_service.hpp"

#include "scenario/goal_scenario.hpp"

using namespace std;

float MAP_SIZE_MIN = -(MAP_SIZE / 2 - HUMUN_SIZE_R);
float MAP_SIZE_MAX = (MAP_SIZE / 2 - HUMUN_SIZE_R);

void GoalScenario::startTurn()
{
    this->humun->loc = {
        getRandf(MAP_SIZE_MIN, MAP_SIZE_MAX),
        HUMUN_SIZE_R,
        getRandf(MAP_SIZE_MIN, MAP_SIZE_MAX),
    };
    this->humun->angle = getRandf(0, 6);

    this->goal->loc = {
        getRandf(MAP_SIZE_MIN, MAP_SIZE_MAX),
        HUMUN_SIZE_R,
        getRandf(MAP_SIZE_MIN, MAP_SIZE_MAX),
    };

    this->moveBefore = 0.;
    this->moveAfter = 0.;

    this->phase_id = "";

    this->inGoal = false;
}

void GoalScenario::capture()
{
    HumunObject *humun = this->humun;

    BeginDrawing();

    RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    BeginTextureMode(target);
    ClearBackground(RAYWHITE);

    BeginMode3D({humun->loc,
                 Vector3Add(humun->loc, Vector3RotateByAxisAngle({3.0, 0., 0.}, {0., 1., 0.}, humun->angle)),
                 Vector3{0.0f, 1.0f, 0.0f},
                 45.0f,
                 CAMERA_PERSPECTIVE});

    Vault::instance().map.draw3D();

    for (BaseObject *basOobj : Vault::instance().object)
    {
        if (basOobj == humun)
            continue;

        ((HumunObject *)basOobj)->draw3D();
    }

    EndMode3D();

    EndTextureMode();

    this->fileName = format("{}\\{}.png", ExePath(), time(0));

    Image image = LoadImageFromTexture(target.texture);
    ImageFlipVertical(&image);

    ExportImage(image, this->fileName.c_str());

    UnloadImage(image);
    UnloadRenderTexture(target);
}

void GoalScenario::mqProduceChoose()
{
    nlohmann::json mqBuffer;

    if (this->phase_id.size() != 0)
    {
        mqBuffer["phase"] = this->phase_id;
    }
    mqBuffer["type"] = "request";
    mqBuffer["turn"] = this->turn - DEFAULT_TURN + 1;
    mqBuffer["filename"] = this->fileName.c_str();

    this->json = mqBuffer.dump();

    thread t(&MQService::sendMessage, this->mqService, this->json.c_str());
    t.detach();
}

void GoalScenario::waitForResponse()
{
    if (!this->mqService->dataQueue.empty())
    {
        nlohmann::json mqBuffer = this->mqService->dataQueue.at(0);
        this->mqService->dataQueue.pop_front();

        this->phase_id = mqBuffer["phase"].template get<string>();
        this->uuid = mqBuffer["uuid"].template get<string>();
        this->angle = mqBuffer["angle"].template get<float>();
        this->frame = 0;
        this->step++;
    }
}

void GoalScenario::changeAngle()
{
    this->frame++;
    HumunObject *humun = this->humun;

    humun->angle += (this->angle / 30);

    if (this->frame == 30)
    {
        this->frame = 0;
        this->step++;
    }
}

void GoalScenario::movePosition()
{
    HumunObject *humun = this->humun;
    GoalObject *goal = this->goal;

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

void GoalScenario::mqProduceResult()
{

    nlohmann::json mqBuffer;

    mqBuffer["type"] = "result";
    mqBuffer["uuid"] = this->uuid;
    mqBuffer["phase"] = this->phase_id;
    mqBuffer["turn"] = this->turn;
    mqBuffer["result"] = this->moveAmount;

    this->json = mqBuffer.dump();

    thread t(&MQService::sendMessage, this->mqService, this->json.c_str());
    t.detach();
}

void GoalScenario::waitForResponseDoNothing()
{
    if (!this->mqService->dataQueue.empty())
    {
        nlohmann::json mqBuffer = this->mqService->dataQueue.at(0);
        this->mqService->dataQueue.pop_front();
        this->step++;
    }
}

void GoalScenario::initialize()
{
}

void GoalScenario::run()
{
    if (IsKeyPressed(KEY_P))
    {
        Vault::instance().object.clear();
        Vault::instance().humun.clear();
        Vault::instance().goal.clear();

        this->humun = new HumunObject({0., HUMUN_SIZE_R, 0.}, 0., BLUE);
        this->goal = new GoalObject({5., HUMUN_SIZE_R, 0.});

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
            this->startTurn();
            this->step++;
            break;

        case 1:
            this->capture();
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
            this->waitForResponseDoNothing();
            break;

        case 8:
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