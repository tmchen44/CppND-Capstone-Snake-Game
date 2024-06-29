#include "snake.h"

#include <cmath>

#include "conversions.h"

void Snake::ChangeDirection(Snake::Direction input,
                            Snake::Direction opposite)
{
  if (direction != opposite || size == 1)
  {
    direction = input;
  }
}

void Snake::Update()
{
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)}; // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
  {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead()
{
  switch (direction)
  {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell)
{
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing)
  {
    // Remove the tail from the vector.
    body.erase(body.begin());
  }
  else
  {
    growing = false;
    size++;
  }
}

void Snake::GrowBody() { growing = true; }

int Snake::GetHeadIndex()
{
  return ConvertCoordinateToFlattened(
      static_cast<int>(head_x),
      static_cast<int>(head_y),
      grid_height);
}

std::vector<int> Snake::GetBodyIndices()
{
  std::vector<int> indices;
  for (auto const &item : body)
  {
    auto index = ConvertCoordinateToFlattened(item.x, item.y, grid_height);
    indices.push_back(index);
  }

  return indices;
}

void Snake::Reset()
{
  head_x = grid_width / 2;
  head_y = grid_height / 2;
  body.clear();
  size = 1;
  speed = 0.1f;
  alive = true;
  growing = false;
}
