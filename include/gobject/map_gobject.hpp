#pragma once

#include <array>

#include "config.hpp"

#include "gobject/base_gobject.hpp"
#include "object/block_object.hpp"

class MapGObject : public BaseGObject
{
private:
    std::array<BlockObject, MAP_WIDTH * MAP_HEIGHT> blocks{};

public:
    MapGObject();
    ~MapGObject();

    void drow() override;
};