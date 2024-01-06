#pragma once

#include <vector>
#include <raylib.h>

#include "gobject/map_gobject.hpp"

class Vault
{
private:
    Vault();
    Vault(const Vault &ref) = delete;
    Vault &operator=(const Vault &ref) = delete;

    static Camera camera;
    static MapGObject map;

public:
    static Camera &getCamera()
    {
        return Vault::camera;
    }

    static MapGObject &getMap()
    {
        return Vault::map;
    }
};