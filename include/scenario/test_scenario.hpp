#pragma once

#include "scenario/base_scenario.hpp"

class TestScenario : public BaseScenario {
public:
    void initialize() override;
    void run() override;
};
