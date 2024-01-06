
#include <random>

#include <raylib.h>

#include "config.hpp"

#include "utils/location.hpp"

#include "object/humun_object.hpp"

HumunObject::HumunObject()
{
    this->color = Color{100, 100, 100};
}

void HumunObject::draw() {}

void HumunObject::draw(Loc loc)
{
    DrawCube(
        Vector3{
            (BLOCK_SIZE + BLOCK_INTERVAL) * loc.x,
            (BLOCK_SIZE + BLOCK_INTERVAL) * loc.y,
            0.0f},
        1.0f, 1.0f, 0.f, BLUE);
}