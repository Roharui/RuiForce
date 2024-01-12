#pragma once

#include "manager/base_manager.hpp"

class HumunMananger : public BaseManager
{
private:
    void MoveToward();
    void SelectHumun();
    void MoveAngle();
    void Capture();

public:
    void run() override;
};
