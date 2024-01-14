
#include <vector>

#include <raylib.h>

#include "core/vault.hpp"

#include "object/humun_object.hpp"

using namespace std;

Vault *Vault::vault = nullptr;

Vault::Vault()
{
    this->camera =
        {
            Vector3{0.0f, CAMERA_INTERVAL, 0.0f}, // Camera position
            Vector3{1.0f, 0.0f, 0.0f},            // Camera looking at point
            Vector3{0.0f, 1.0f, 0.0f},            // Camera up vector (rotation towards target)
            45.0f,                                // Camera field-of-view Y
            CAMERA_PERSPECTIVE                    // Camera projection type
        };

    this->map = MapGObject();

    this->object = vector<BaseObject *>();
    this->humun = vector<HumunObject *>();
    this->goal = vector<GoalObject *>();
}

void Vault::initialize()
{
}

void Vault::draw2D()
{
    for (BaseObject *obj : this->object)
    {
        obj->draw2D();
    }
}

void Vault::draw3D()
{
    BeginMode3D(this->camera);

    this->map.draw3D();

    for (BaseObject *obj : this->object)
    {
        obj->draw3D();
    }

    EndMode3D();
}