
#include <iostream>

#include <raylib.h>

#include "config.hpp"

#include "object/block_object.hpp"

BlockObject::BlockObject()
{
}
BlockObject::BlockObject(int locX, int locY)
{
    this->position = Vector3{(2.0f + BLOCK_INTERVAL) * locX, (2.0f + BLOCK_INTERVAL) * locY, 0.0f};
}
void BlockObject::drow()
{
    DrawCube(this->position, 2.0f, 2.0f, 0.0f, RED);
}