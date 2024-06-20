#ifndef CONVERSIONS_H
#define CONVERSIONS_H

// Converts x and y coordinates to flattened index.
int ConvertCoordinateToFlattened(int x, int y, int grid_height);

// Gets x coordinate from flattened index.
int GetXFromIndex(int index, int grid_width);

// Gets y coordinate from flattened index.
int GetYFromIndex(int index, int grid_width);

#endif
