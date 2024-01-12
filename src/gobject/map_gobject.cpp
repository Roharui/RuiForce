
#include "config.hpp"

#include "utils/location.hpp"

#include "gobject/map_gobject.hpp"

#include "object/humun_object.hpp"

MapGObject::MapGObject()
{
}

MapGObject::~MapGObject()
{
}

void MapGObject::draw()
{
    DrawGrid(10, HUMUN_SIZE);
}