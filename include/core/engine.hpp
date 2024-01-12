#pragma once

#include <vector>

#include "manager/base_manager.hpp"
#include "manager/camera_manager.hpp"
#include "manager/humun_manager.hpp"

class Engine
{
private:
    Engine() = delete;
    Engine(const Engine &ref) = delete;
    Engine &operator=(const Engine &ref) = delete;

    static int waitTick;
    static std::vector<BaseManager *> managers;

    // manager initialize ===

    template <class T>
    static void pushManager()
    {
        BaseManager *manager = new T();
        Engine::managers.push_back(manager);
    }

public:
    // run engine ===

    static void initialize()
    {
        Engine::pushManager<CameraManager>();
        Engine::pushManager<HumunMananger>();
    }

    static void run()
    {
        for (BaseManager *manager : Engine::managers)
        {
            manager->run();
        }
    }

    // animation ==

    static bool wait()
    {
        return Engine::waitTick > 0;
    }

    static void tictok()
    {
        if (Engine::waitTick > 0)
            Engine::waitTick--;
    }

    static int getWait()
    {
        return Engine::waitTick;
    }

    static void setWait(int time)
    {
        Engine::waitTick = time;
    }
};