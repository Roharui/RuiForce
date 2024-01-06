#pragma once

#include <vector>

#include <raylib.h>

#include "utils/location.hpp"

#include "object/base_object.hpp"
#include "object/humun_object.hpp"

class BlockObject : public BaseObject
{
private:
    Loc loc;
    std::vector<HumunObject *> humuns{};

public:
    BlockObject();
    BlockObject(Loc loc);

    void addHumun(HumunObject *humun);

    void draw() override;
};