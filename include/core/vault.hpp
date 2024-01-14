#pragma once

#include <vector>
#include <raylib.h>

#include "config.hpp"

#include "object/humun_object.hpp"
#include "object/goal_object.hpp"

#include "gobject/map_gobject.hpp"

using namespace std;

class Vault
{
private:
    Vault();
    Vault(const Vault &ref) = delete;
    Vault &operator=(const Vault &ref) = delete;

    static Vault *vault;

public:
    Camera camera;
    MapGObject map;
    vector<BaseObject *> object;
    vector<HumunObject *> humun;
    vector<GoalObject *> goal;

    void initialize();

    void draw2D();
    void draw3D();

    static Vault &instance()
    {
        if (Vault::vault == nullptr)
        {
            Vault::vault = new Vault();
        }

        return *Vault::vault;
    }
};