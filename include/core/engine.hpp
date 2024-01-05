#pragma once

#include <vector>

#include "manager/base_manager.hpp"

class Engine
{
private:
    Engine();
    Engine(const Engine &ref) = delete;
    Engine &operator=(const Engine &ref) = delete;
    std::vector<BaseManager *> managers;

    static Engine *s;

public:
    int waitTick;
    static Engine &instance()
    {
        if (s == nullptr)
        {
            s = new Engine();
        }
        return *s;
    }

    static bool wait()
    {
        if (s == nullptr)
        {
            s = new Engine();
        }
        return s->waitTick > 0;
    }

    static void tictok()
    {
        if (s == nullptr)
        {
            s = new Engine();
        }
        if (s->waitTick > 0)
            s->waitTick--;
    }

    static void setWait(int time)
    {
        if (s == nullptr)
        {
            s = new Engine();
        }
        s->waitTick = time;
    }

    void run();
};