
#include <vector>

#include "core/engine.hpp"

#include "manager/base_manager.hpp"
#include "manager/camera_manager.hpp"
#include "manager/humun_manager.hpp"

using namespace std;

Engine *Engine::engine = nullptr;

Engine::Engine()
{
}

void Engine::initialize(BaseScenario *scenario)
{
    this->pushManager<CameraManager>();
    this->pushManager<HumunMananger>();

    this->scenario = scenario;
    this->scenario->initialize();
}

template <class T>
void Engine::pushManager()
{
    BaseManager *manager = new T();
    this->managers.push_back(manager);
}

void Engine::run()
{
    for (BaseManager *manager : this->managers)
    {
        manager->run();
    }
    this->scenario->run();
}