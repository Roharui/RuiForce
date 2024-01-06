#pragma once

#include <raylib.h>

#include "object/base_object.hpp"

class BlockObject : public BaseObject
{
private:
    Vector3 position = {0.0f, 0.0f, 0.0f};

public:
    BlockObject();
    BlockObject(int locX, int locY);
    void drow() override;
};