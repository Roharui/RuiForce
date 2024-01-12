#pragma once

#include <raylib.h>

#include "config.hpp"

#include "utils/location.hpp"

#include "object/base_object.hpp"

class HumunObject : public BaseObject
{
private:
public:
    Color color;
    Vector3 loc;
    Vector3 size = {HUMUN_SIZE,
                    HUMUN_SIZE,
                    HUMUN_SIZE};
    float angle;
    bool selected = false;

    int goFrame = FPS;
    int action = -1;

    HumunObject();
    HumunObject(Vector3 loc, float angle, Color color);

    void draw2D() override;
    void draw3D() override;
};