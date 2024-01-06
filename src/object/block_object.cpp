
#include <iostream>
#include <vector>

#include <raylib.h>

#include "config.hpp"

#include "utils/location.hpp"

#include "object/block_object.hpp"
#include "object/humun_object.hpp"

BlockObject::BlockObject()
{
}

BlockObject::BlockObject(Loc loc)
{
    this->loc = loc;
    this->humuns = std::vector<HumunObject *>();
}

void BlockObject::addHumun(HumunObject *humun)
{
    this->humuns.push_back(humun);
}

void BlockObject::draw()
{
    DrawCube(
        Vector3{
            (BLOCK_SIZE + BLOCK_INTERVAL) * this->loc.x,
            (BLOCK_SIZE + BLOCK_INTERVAL) * this->loc.y,
            0.0f,
        },
        BLOCK_SIZE, BLOCK_SIZE, 0.0f,
        RED);

    for (HumunObject *humun : this->humuns)
    {
        humun->draw(this->loc);
    }
}