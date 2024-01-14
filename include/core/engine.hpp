#pragma once

#include <vector>

#include "scenario/goal_senario.hpp"

#include "manager/base_manager.hpp"
#include "manager/camera_manager.hpp"
#include "manager/humun_manager.hpp"

#include "scenario/base_senario.hpp"

using namespace std;

class Engine
{
private:
    Engine();
    Engine(const Engine &ref) = delete;
    Engine &operator=(const Engine &ref) = delete;

    vector<BaseManager *> managers;
    BaseScenario *scenario;

    template <class T>
    void pushManager();

    static Engine *engine;

public:
    void initialize(BaseScenario* scenario);

    void run();

    static Engine &instance()
    {
        if (Engine::engine == nullptr)
        {
            Engine::engine = new Engine();
        }

        return *Engine::engine;
    }
};