#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "SDL.h"

class Snake
{
public:
  enum Direction
  {
    kUp,
    kDown,
    kLeft,
    kRight
  };

  Snake(
      int grid_width,
      int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();
  void Reset();
  void ChangeDirection(Snake::Direction input, Snake::Direction opposite);
  void GrowBody();

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  const int grid_width;
  const int grid_height;

  int GetHeadIndex();
  std::vector<int> GetBodyIndices();

private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  Direction direction = Direction::kUp;
};

#endif
