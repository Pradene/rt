#include "../../includes/minirt.h"

float   dot(v3 p, v3 q)
{
    return (p.x * q.x + p.y * q.y + p.z * q.z);
}

v3  normalize(v3 vec)
{
    float   magnitude;

    magnitude = sqrt(dot(vec, vec));
    return (vec / magnitude);
}
