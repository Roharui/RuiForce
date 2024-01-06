
#include <vector>

#include "core/engine.hpp"

#include "manager/base_manager.hpp"

int Engine::waitTick = 0;
std::vector<BaseManager *> Engine::managers;
