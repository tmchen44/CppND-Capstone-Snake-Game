#include "conversions.h"

int ConvertCoordinateToFlattened(int x, int y, int grid_height)
{
    return x + (y * grid_height);
}

int GetXFromIndex(int index, int grid_width)
{
    return index % grid_width;
}

int GetYFromIndex(int index, int grid_width)
{
    return index / grid_width;
}
