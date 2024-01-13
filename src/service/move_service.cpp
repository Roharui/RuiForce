
#include <raymath.h>

#include "config.hpp"

#include "service/move_service.hpp"

Vector3 MoveToward(Vector3 loc, float direction, float angle)
{
    loc = Vector3Add(loc, Vector3RotateByAxisAngle({HUMUN_MOVE_SPEED * direction, 0., 0.}, {0., 1., 0.}, angle));

    float MAP_SIZE_MIN = -(MAP_SIZE / 2 - HUMUN_SIZE_R);
    float MAP_SIZE_MAX = (MAP_SIZE / 2 - HUMUN_SIZE_R);

    loc = Vector3Min(loc, {MAP_SIZE_MAX, 99., MAP_SIZE_MAX});
    loc = Vector3Max(loc, {MAP_SIZE_MIN, 00., MAP_SIZE_MIN});

    return loc;
}