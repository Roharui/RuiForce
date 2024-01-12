#pragma once

#include <vector>
#include <raylib.h>

#include "config.hpp"

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
    static std::vector<BaseObject *> object;

public:
    static void initialize()
    {
        HumunObject *h1 = new HumunObject({0., HUMUN_MIN_Y, 0.}, 0., BLUE);
        Vault::getObject().push_back(h1);

        HumunObject *h2 = new HumunObject({10., HUMUN_MIN_Y, 0.}, 0., BLUE);
        Vault::getObject().push_back(h2);
    }

    static Camera &getCamera()
    {
        return Vault::camera;
    }

    static MapGObject &getMap()
    {
        return Vault::map;
    }

    static std::vector<BaseObject *> &getObject()
    {
        return Vault::object;
    }

    static void draw()
    {
        Vault::getMap().draw();

        for (BaseObject *obj : Vault::getObject())
        {
            obj->draw3D();
        }
    }
};