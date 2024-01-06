#pragma once

#include <raylib.h>

class Driver
{

public:
    Driver();
    void Run();

private:
    void Initialize();
    void Update();
    void draw();
};
