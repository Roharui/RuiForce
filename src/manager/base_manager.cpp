
#include "core/engine.hpp"
#include "manager/base_manager.hpp"

bool BaseManager::doseWait()
{
    return Engine::wait();
}

void BaseManager::wait(int time)
{
    Engine::setWait(time);
}