#include "game_state.h"

#include <unordered_set>
#include "conversions.h"

GameState::GameState(
    std::size_t grid_width,
    std::size_t grid_height,
    std::vector<std::unique_ptr<Level>> &levels)
    : snake(grid_width, grid_height),
      engine(dev()),
      levels(levels)
{
    ResetViewIndex();
    SetViewLevelAsCurrentLevel();
    PlaceFood();
}

void GameState::NextViewIndex()
{
    view_index++;
    if (view_index >= levels.size())
    {
        // Allow wrap-around.
        view_index = 0;
    }
}

void GameState::PreviousViewIndex()
{
    if (view_index == 0)
    {
        // Allow wrap-around.
        view_index = levels.size() - 1;
    }
    else
    {
        view_index--;
    }
}

void GameState::CheckSnakeCollision()
{
    auto head_x = static_cast<int>(snake.head_x);
    auto head_y = static_cast<int>(snake.head_y);

    int head_index = ConvertCoordinateToFlattened(
        head_x, head_y, snake.grid_height);

    std::unordered_set<int> obstacle_indices;
    // Add snake body.
    auto snake_indices = snake.GetBodyIndices();
    obstacle_indices.insert(snake_indices.begin(), snake_indices.end());

    // Add level obstacles.
    auto level_obstacles =
        current_level->GetIndicesByGridContent()[GridContent::OBSTACLE];
    for (auto index : level_obstacles)
    {
        obstacle_indices.insert(index);
    }

    if (obstacle_indices.count(head_index) == 1)
    {
        snake.alive = false;
    }
}

void GameState::PlaceFood()
{
    std::unordered_set<int> open_spaces;

    // Start with open level spaces.
    auto level_open =
        current_level->GetIndicesByGridContent()[GridContent::EMPTY];
    open_spaces.insert(level_open.begin(), level_open.end());

    // // Remove spaces occupied by snake.
    open_spaces.erase(snake.GetHeadIndex());
    auto body_indices = snake.GetBodyIndices();
    for (auto index : body_indices)
    {
        open_spaces.erase(index);
    }

    // // Check if there are spaces left.
    if (open_spaces.size() == 0)
    {
        return;
    }

    // Choose random index for one of the open spaces.
    std::uniform_int_distribution<int>
        random(
            0, static_cast<int>(open_spaces.size() - 1));
    int spaces_index = random(engine);

    std::vector<int> spaces(open_spaces.begin(), open_spaces.end());
    int food_index = spaces[spaces_index];
    food.x = GetXFromIndex(food_index, snake.grid_width);
    food.y = GetYFromIndex(food_index, snake.grid_width);
}

void GameState::UpdateGame()
{
    if (!snake.alive)
        return;

    snake.Update();
    CheckSnakeCollision();

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y)
    {
        score++;
        PlaceFood();
        // Grow snake and increase speed.
        snake.GrowBody();
        snake.speed += 0.02;
    }
}

void GameState::ResetGame()
{
    ResetScore();
    snake.Reset();
    PlaceFood();
}
