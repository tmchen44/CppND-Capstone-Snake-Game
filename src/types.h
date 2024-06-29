#ifndef TYPES_H
#define TYPES_H

#include <cstddef>
#include <string>

struct Dimension
{
    std::size_t width;
    std::size_t height;
};

struct SaveData
{
    std::string date_time;
    std::string level_name;
    int score;
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
