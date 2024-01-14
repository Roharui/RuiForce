#pragma once

class BaseObject
{
private:
    virtual void push() = 0;

public:
    virtual void draw2D() = 0;
    virtual void draw3D() = 0;
};