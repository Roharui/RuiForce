
#include <raylib.h>
#include <raymath.h>

#include "config.hpp"

#include "gobject/map_gobject.hpp"

#include "object/humun_object.hpp"

MapGObject::MapGObject()
{
}

MapGObject::~MapGObject()
{
}

void MapGObject::draw3D()
{
    DrawCube(Vector3Zero(), MAP_SIZE, 0, MAP_SIZE, GRAY);
}