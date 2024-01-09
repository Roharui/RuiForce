
#include "config.hpp"

#include "utils/location.hpp"

#include "gobject/map_gobject.hpp"
#include "object/block_object.hpp"

#include "object/humun_object.hpp"

MapGObject::MapGObject()
{
    for (int i = 0; i < MAP_WIDTH; i++)
    {
        for (int j = 0; j < MAP_HEIGHT; j++)
        {
            BlockObject block(Loc{i, j});
            this->blocks[i + MAP_WIDTH * j] = block;
        }
    }
}

MapGObject::~MapGObject()
{
}

BlockObject &MapGObject::getBlocks(Loc loc)
{
    return this->blocks[loc.x + MAP_WIDTH * loc.y];
}

void MapGObject::draw()
{
    DrawGrid(30, 1.0f);
}