#pragma once

#include <raylib.h>

#include "utils/location.hpp"

#include "object/base_object.hpp"

class HumunObject : public BaseObject
{
private:
    Color color;
    Vector3 loc;

public:
    HumunObject();
    HumunObject(Vector3 loc);
    void draw() override;
};