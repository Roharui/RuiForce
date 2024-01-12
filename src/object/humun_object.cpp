
#include <random>

#include <raylib.h>

#include "config.hpp"

#include "utils/location.hpp"

#include "object/humun_object.hpp"

HumunObject::HumunObject()
    : HumunObject({0., 0., 0.})
{
}

HumunObject::HumunObject(Vector3 loc)
    : loc(loc)
{
    this->color = BLUE;
}

void HumunObject::draw()
{
    DrawCube(this->loc, HUMUN_SIZE, HUMUN_SIZE, HUMUN_SIZE, BLUE);
    DrawCube({this->loc.x + HUMUN_SIZE / 2, this->loc.y, this->loc.z}, HUMUN_SIZE / 2, HUMUN_SIZE / 4, HUMUN_SIZE / 4, RED);
    DrawCubeWires(this->loc, HUMUN_SIZE, HUMUN_SIZE, HUMUN_SIZE, BLACK);
}
