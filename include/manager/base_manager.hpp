#pragma once

class BaseManager
{
protected:
    bool doseWait();
    void wait(int time);

public:
    virtual void run() = 0;
};