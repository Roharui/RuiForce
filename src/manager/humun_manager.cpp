
#include <raylib.h>
#include <raymath.h>

#include "core/vault.hpp"
#include "core/engine.hpp"

#include "manager/humun_manager.hpp"
#include "object/humun_object.hpp"

using namespace std;

HumunObject *HumunMananger::getHumun()
{
    return (HumunObject *)Vault::instance().object.at(this->select);
}

void HumunMananger::MoveLoc()
{

    if (IsKeyDown(KEY_UP))
    {
        HumunObject *humun = this->getHumun();
        this->MoveToward();
    }
    if (IsKeyDown(KEY_DOWN))
    {
        HumunObject *humun = this->getHumun();
        this->MoveToward();
    }
}

void HumunMananger::MoveToward()
{
    // HumonService;
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
    select %= Vault::instance().object.size();

    for (BaseObject *humun : Vault::instance().object)
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