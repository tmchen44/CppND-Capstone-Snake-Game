#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "scene.h"

class Controller
{
public:
    void HandleInput(Scene *scene) const;
};

#endif
