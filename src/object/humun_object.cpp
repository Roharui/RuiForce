
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
    DrawCube(Vector3{0.0f, HUMUN_SIZE / 2, 0.0f},
             HUMUN_SIZE, HUMUN_SIZE, HUMUN_SIZE, BLUE);
    DrawCubeWires(Vector3{0.0f, HUMUN_SIZE / 2, 0.0f},
                  HUMUN_SIZE, HUMUN_SIZE, HUMUN_SIZE, BLACK);
}