
#include <raylib.h>

#include "config.hpp"

#include "object/goal_object.hpp"

GoalObject::GoalObject() : GoalObject({5., HUMUN_SIZE_R, 0.})
{
}

GoalObject::GoalObject(Vector3 loc) : loc(loc)
{
}

void GoalObject::draw2D()
{
}

void GoalObject::draw3D()
{
    DrawCubeV(this->loc, this->size, this->color);
    DrawCubeWiresV(this->loc, this->size, BLACK);
}