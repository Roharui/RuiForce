
#include <raylib.h>

#include "core/vault.hpp"

Vault *Vault::v = nullptr;

Vault::Vault()
{
    this->camera =
        {
            Vector3{00.0f, 0.0f, 10.0f}, // Camera position
            Vector3{0.0f, 0.0f, 0.0f},   // Camera looking at point
            Vector3{0.0f, 1.0f, 0.0f},   // Camera up vector (rotation towards target)
            45.0f,                       // Camera field-of-view Y
            CAMERA_PERSPECTIVE           // Camera projection type
        };
}