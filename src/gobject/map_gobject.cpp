
#include "config.hpp"

#include "gobject/map_gobject.hpp"
#include "object/block_object.hpp"

MapGObject::MapGObject()
{
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_HEIGHT; j++)
        {
            BlockObject block(i, j);
            this->blocks[i + MAP_WIDTH * j] = block;
        }
    }
}

MapGObject::~MapGObject()
{
}

void MapGObject::drow()
{
    for (BlockObject &s : this->blocks)
    {
        s.drow();
    }
}