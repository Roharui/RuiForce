#pragma once

#include <vector>
#include <raylib.h>

class Vault
{
private:
    Vault();
    Vault(const Vault &ref) = delete;
    Vault &operator=(const Vault &ref) = delete;
    static Vault *v;

public:
    Camera camera;

    static Vault &instance()
    {
        if (v == nullptr)
        {
            v = new Vault();
        }
        return *v;
    }
};