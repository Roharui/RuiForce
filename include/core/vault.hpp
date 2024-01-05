#pragma once

#include <vector>
#include <raylib.h>

class Vault
{
private:
    Vault();
    Vault(const Vault &ref) = delete;
    Vault &operator=(const Vault &ref) = delete;

public:
    Camera camera;

    static Vault &instance()
    {
        static Vault s;
        return s;
    }
};