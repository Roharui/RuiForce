
#include "core/engine.hpp"

#include "manager/camera_manager.hpp"

Engine *Engine::s = nullptr;

Engine::Engine()
{
    this->waitTick = 0;

    BaseManager *cameraManager = new CameraManager();

    this->managers.push_back(cameraManager);
}

void Engine::run()
{
    for (BaseManager *manager : this->managers)
    {
        manager->run();
    }
}