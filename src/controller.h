#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "scene.h"
#include "snake.h"

class Controller
{
public:
    void HandleInput(Scene *scene) const;
};

#endif
