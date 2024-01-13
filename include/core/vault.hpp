#pragma once

#include <vector>
#include <raylib.h>

#include "config.hpp"

#include "object/humun_object.hpp"
#include "object/goal_object.hpp"

#include "gobject/map_gobject.hpp"

class Vault
{
private:
    Vault() = delete;
    Vault(const Vault &ref) = delete;
    Vault &operator=(const Vault &ref) = delete;

public:
    static Camera camera;
    static MapGObject map;
    static std::vector<BaseObject *> object;
    static HumunObject *humun;
    static GoalObject *goal;

    static void initialize()
    {
        HumunObject *humun = new HumunObject({0., HUMUN_SIZE_R, 0.}, 0., BLUE);
        Vault::object.push_back(humun);
        Vault::humun = humun;

        GoalObject *goal = new GoalObject({5., HUMUN_SIZE_R, 0.});
        Vault::object.push_back(goal);
        Vault::goal = goal;
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

    static void draw2D()
    {
        for (BaseObject *obj : Vault::getObject())
        {
            obj->draw2D();
        }
    }

    static void draw3D()
    {
        BeginMode3D(Vault::getCamera());

        Vault::getMap().draw3D();

        for (BaseObject *obj : Vault::getObject())
        {
            obj->draw3D();
        }

        EndMode3D();
    }
};