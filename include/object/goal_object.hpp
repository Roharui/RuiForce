#pragma once

#include <raylib.h>

#include "config.hpp"

#include "object/base_object.hpp"

class GoalObject : public BaseObject
{
private:
public:
    Color color = PURPLE;
    Vector3 loc;
    Vector3 size = {HUMUN_SIZE,
                    HUMUN_SIZE,
                    HUMUN_SIZE};

    void draw2D() override;
    void draw3D() override;

    GoalObject();
    GoalObject(Vector3 loc);
};