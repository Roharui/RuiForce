
#include <raylib.h>

#include "config.hpp"

#include "core/vault.hpp"

#include "object/goal_object.hpp"

GoalObject::GoalObject() : GoalObject({5., HUMUN_SIZE_R, 0.})
{
}

GoalObject::GoalObject(Vector3 loc) : loc(loc)
{
    this->push();
}

void GoalObject::push()
{
    Vault::instance().object.push_back(this);
    Vault::instance().goal.push_back(this);
}

void GoalObject::draw2D()
{
}

void GoalObject::draw3D()
{
    DrawCubeV(this->loc, this->size, this->color);
    DrawCubeWiresV(this->loc, this->size, BLACK);
}