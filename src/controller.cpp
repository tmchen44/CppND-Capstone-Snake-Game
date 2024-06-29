#include "controller.h"

#include "SDL.h"

#include "scene.h"
#include "snake.h"
#include "types.h"

void Controller::HandleInput(Scene *scene) const
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      scene->StoreCommand(Command::QUIT);
    }
    else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
      switch (e.key.keysym.sym)
      {
      case SDLK_UP:
        scene->StoreCommand(Command::UP);
        break;

      case SDLK_DOWN:
        scene->StoreCommand(Command::DOWN);
        break;

      case SDLK_LEFT:
        scene->StoreCommand(Command::LEFT);
        break;

      case SDLK_RIGHT:
        scene->StoreCommand(Command::RIGHT);
        break;

      case SDLK_ESCAPE:
        scene->StoreCommand(Command::ESCAPE);
        break;

      case SDLK_RETURN:
        scene->StoreCommand(Command::ENTER);
        break;
      }
    }
  }
}
