
#include <random>
#include <string>
#include <format>

#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include "config.hpp"

#include "core/vault.hpp"

#include "utils/location.hpp"

#include "object/humun_object.hpp"

HumunObject::HumunObject()
    : HumunObject({0., HUMUN_SIZE_R, 0.}, 0., BLUE)
{
}

HumunObject::HumunObject(Vector3 loc, float angle, Color color)
{
    this->loc = loc;
    this->angle = angle;
    this->color = color;
}

void HumunObject::draw2D()
{
    // std::string msg{std::format("x : {}, z : {}, angle : {}", this->loc.x, this->loc.z, this->angle)};
    // DrawText(msg.c_str(), 0, 0, 10, BLACK);
}

void HumunObject::draw3D()
{
    DrawCubeV(this->loc, this->size, this->color);

    Vector3 target = Vector3Add(this->loc, Vector3RotateByAxisAngle({3.0, 0, 0}, {0, 1, 0}, this->angle));
    DrawCube(target, HUMUN_SIZE / 4, HUMUN_SIZE / 4, HUMUN_SIZE / 4, RED);
    DrawCubeWiresV(this->loc, this->size, this->selected ? RED : BLACK);
}
