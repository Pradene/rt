#include "../../includes/minirt.h"

int rgba_to_color(float r, float g, float b, float a)
{
    int color;

    r = clamp(r, 0.0, 1.0);
    g = clamp(g, 0.0, 1.0);
    b = clamp(b, 0.0, 1.0);
    a = clamp(a, 0.0, 1.0);
    color = ((int)(a * 255) << 24) | ((int)(r * 255) << 16) \
    | ((int)(g * 255) << 8) | ((int)(b * 255) << 0);
    return (color);
}
