
#include <stdlib.h>

#include "utils/random.hpp"

float getRandf(float min, float max)
{
    return min + (rand() / (RAND_MAX / (max - min)));
}