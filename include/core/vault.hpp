#pragma once

#include <vector>
#include <raylib.h>

#include "object/humun_object.hpp"
#include "gobject/map_gobject.hpp"

class Vault
{
private:
    Vault() = delete;
    Vault(const Vault &ref) = delete;
    Vault &operator=(const Vault &ref) = delete;

    static Camera camera;
    static MapGObject map;
    static std::vector<HumunObject *> humuns;

public:
    static void initialize()
    {
        HumunObject *h1 = new HumunObject();
        Vault::gethumuns().push_back(h1);
        Vault::getMap().getBlocks({0, 0}).addHumun(h1);

        HumunObject *h2 = new HumunObject();
        Vault::gethumuns().push_back(h2);
        Vault::getMap().getBlocks({3, 3}).addHumun(h2);

        HumunObject *h3 = new HumunObject();
        Vault::gethumuns().push_back(h3);
        Vault::getMap().getBlocks({5, 3}).addHumun(h3);

        HumunObject *h4 = new HumunObject();
        Vault::gethumuns().push_back(h4);
        Vault::getMap().getBlocks({7, 7}).addHumun(h4);
    }

    static Camera &getCamera()
    {
        return Vault::camera;
    }

    static MapGObject &getMap()
    {
        return Vault::map;
    }

    static std::vector<HumunObject *> &gethumuns()
    {
        return Vault::humuns;
    }
};