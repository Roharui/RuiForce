#pragma once

#include "manager/base_manager.hpp"

#include "object/humun_object.hpp"

class HumunMananger : public BaseManager
{
private:
    int select = 0;
    HumunObject *getHumun();

public:
    void MoveLoc();
    void MoveToward();
    void SelectHumun();
    void MoveAngle(float angle);

    void run() override;
};
