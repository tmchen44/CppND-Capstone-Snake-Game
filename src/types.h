#ifndef TYPES_H
#define TYPES_H

#include <cstddef>

struct Dimension
{
    std::size_t width;
    std::size_t height;
};

enum GridContent
{
    EMPTY,
    OBSTACLE,
};

enum SceneName
{
    LEVEL,
    GAME,
};

enum Command
{
    NONE,
    QUIT,
    ESCAPE,
    ENTER,
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

#endif
