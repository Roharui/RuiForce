#pragma once

#include <vector>

#include <raylib.h>

#include "config.hpp"

#include "object/base_object.hpp"

using namespace std;

class HumunObject : public BaseObject
{
private:
    void push() override;

public:
    Color color;
    Vector3 loc;
    Vector3 size = {HUMUN_SIZE,
                    HUMUN_SIZE,
                    HUMUN_SIZE};
    float angle;
    bool selected = false;

    HumunObject();
    HumunObject(Vector3 loc, float angle, Color color);

    void draw2D() override;
    void draw3D() override;
};