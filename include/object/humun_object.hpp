#pragma once

#include <raylib.h>

#include "utils/location.hpp"

#include "object/base_object.hpp"

class HumunObject : public BaseObject
{
private:
    Color color;

public:
    HumunObject();
    void draw() override;
    void draw(Loc loc);
};