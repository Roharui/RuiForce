#pragma once

class BaseScenario
{
public:
    virtual void initialize() = 0;
    virtual void run() = 0;
};