
#include <raylib.h>
#include <raymath.h>

#include "core/vault.hpp"
#include "core/engine.hpp"

#include "manager/humun_manager.hpp"
#include "object/humun_object.hpp"

using namespace std;

HumunObject *HumunMananger::getHumun()
{
    return (HumunObject *)Vault::getObject().at(this->select);
}

void HumunMananger::MoveLoc()
{
    HumunObject *humun = this->getHumun();

    if (IsKeyDown(KEY_UP))
    {
        humun->action = 1;
        this->MoveToward();
    }
    if (IsKeyDown(KEY_DOWN))
    {
        humun->action = -1;
        this->MoveToward();
    }
}

void HumunMananger::MoveToward()
{
    HumunObject *humun = this->getHumun();

    humun->loc = Vector3Add(humun->loc, Vector3RotateByAxisAngle({HUMUN_MOVE_SPEED * humun->action, 0., 0.}, {0., 1., 0.}, humun->angle));

    float MAP_SIZE_MIN = -(MAP_SIZE / 2 - HUMUN_SIZE_R);
    float MAP_SIZE_MAX = (MAP_SIZE / 2 - HUMUN_SIZE_R);

    humun->loc = Vector3Min(humun->loc, {MAP_SIZE_MAX, 99., MAP_SIZE_MAX});
    humun->loc = Vector3Max(humun->loc, {MAP_SIZE_MIN, 00., MAP_SIZE_MIN});
}

void HumunMananger::MoveAngle(float angle)
{
    HumunObject *humun = this->getHumun();
    humun->angle += angle;
}

void HumunMananger::SelectHumun()
{
    return; // 현재는 사용 안함.

    select += 1;
    select %= Vault::getObject().size();

    for (BaseObject *humun : Vault::getObject())
    {
        ((HumunObject *)humun)->selected = false;
    }

    ((HumunObject *)this->getHumun())->selected = true;
}

void HumunMananger::run()
{
    if (IsKeyDown(KEY_TAB))
    {
        this->SelectHumun();
    }

    this->MoveLoc();

    if (IsKeyDown(KEY_LEFT))
    {
        this->MoveAngle(ANGLE_MOVE_SPEED);
    }

    if (IsKeyDown(KEY_RIGHT))
    {
        this->MoveAngle(-ANGLE_MOVE_SPEED);
    }
}