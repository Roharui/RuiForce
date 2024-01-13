
#include <raylib.h>
#include <raymath.h>

#include "core/vault.hpp"

bool CheckCollisionBoxesV(Vector3 loc1, Vector3 size1, Vector3 loc2, Vector3 size2)
{
    Vector3 size_r1 = Vector3Divide(size1, {2, 2, 2});
    Vector3 size_r2 = Vector3Divide(size2, {2, 2, 2});

    Vector3 down_loc1 = Vector3Subtract(loc1, size_r1);
    Vector3 up_loc1 = Vector3Add(loc1, size_r1);

    Vector3 down_loc2 = Vector3Subtract(loc2, size_r2);
    Vector3 up_loc2 = Vector3Add(loc2, size_r2);

    return CheckCollisionBoxes(
        BoundingBox{
            down_loc1,
            up_loc1,
        },
        BoundingBox{
            down_loc2,
            up_loc2,
        });
}
