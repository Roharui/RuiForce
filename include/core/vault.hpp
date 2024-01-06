#pragma once

#include <vector>
#include <raylib.h>

class Vault
{
private:
    Vault();
    Vault(const Vault &ref) = delete;
    Vault &operator=(const Vault &ref) = delete;

    static Camera camera;

public:
    static Camera &getCamera()
    {
        return Vault::camera;
    }
};