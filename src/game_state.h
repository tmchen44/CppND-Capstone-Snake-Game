#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <random>
#include "level.h"
#include "SDL.h"
#include "snake.h"

// Class representing the state of the game.
class GameState
{
public:
    GameState(std::size_t grid_width,
              std::size_t grid_height,
              std::vector<std::unique_ptr<Level>> &levels);

    // Game-related
    void ResetGame();
    void UpdateGame();
    int GetSize() const { return snake.size; }
    void PlaceFood();
    void CheckSnakeCollision();
    Snake &GetSnake() { return snake; }
    SDL_Point &GetFood() { return food; }

    bool IsRunning() { return running; }
    void StopGame() { running = false; }

    // Score-related.
    int GetScore() const { return score; }

    // Level-related.
    Level *GetCurrentLevel() const { return current_level; }
    Level *GetLevelAtViewIndex() const { return levels[view_index].get(); }
    void SetViewLevelAsCurrentLevel()
    {
        current_level = levels[view_index].get();
    }
    void ResetViewIndex() { view_index = 0; }
    void NextViewIndex();
    void PreviousViewIndex();

private:
    void ResetScore() { score = 0; }

    Snake snake;
    SDL_Point food;
    // Current in-game level.
    Level *current_level;
    // levels index of the Level that is being viewed in level select.
    std::size_t view_index;

    int score{0};
    bool running = true;

    // Game state that doesn't require management.
    std::random_device dev;
    std::mt19937 engine;

    // Read-only vector of all levels.
    std::vector<std::unique_ptr<Level>> &levels;
};

#endif
