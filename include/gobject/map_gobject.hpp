#pragma once

#include <array>

#include "config.hpp"

#include "gobject/base_gobject.hpp"

using namespace std;

class MapGObject : public BaseGObject
{

public:
    MapGObject();
    ~MapGObject();

    void draw3D() override;
};