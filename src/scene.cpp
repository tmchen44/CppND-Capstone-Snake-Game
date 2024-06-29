#include "scene.h"

#include "conversions.h"
#include "snake.h"
#include "types.h"

SceneName LevelScene::GetSceneName() { return SceneName::LEVEL; }

void LevelScene::Update(GameState &game_state)
{
    Command command = GetCommand();
    switch (command)
    {
    case Command::LEFT:
        game_state.PreviousViewIndex();
        break;
    case Command::RIGHT:
        game_state.NextViewIndex();
        break;
    }
}

void LevelScene::Render(Renderer &renderer, GameState &game_state)
{
    Level *view_level = game_state.GetLevelAtViewIndex();

    SDL_Rect block;
    block.w = renderer.screen_width / renderer.grid_width;
    block.h = renderer.screen_height / renderer.grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(renderer.GetSdlRenderer(), 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(renderer.GetSdlRenderer());

    // Render level (gray)
    SDL_SetRenderDrawColor(renderer.GetSdlRenderer(), 175, 175, 175, 255);
    std::vector<int> obstacle_indices = view_level->GetIndicesByGridContent()
                                            .at(GridContent::OBSTACLE);
    for (int index : obstacle_indices)
    {
        int x = index % renderer.grid_width;
        int y = index / renderer.grid_width;
        block.x = x * block.w;
        block.y = y * block.h;
        SDL_RenderFillRect(renderer.GetSdlRenderer(), &block);
    }

    // Update Screen
    SDL_RenderPresent(renderer.GetSdlRenderer());
}

SceneName GameScene::GetSceneName() { return SceneName::GAME; }

void GameScene::Update(GameState &game_state)
{
    Command command = GetCommand();
    switch (command)
    {
    case Command::LEFT:
        game_state.GetSnake().ChangeDirection(
            Snake::Direction::kLeft, Snake::Direction::kRight);
        break;
    case Command::RIGHT:
        game_state.GetSnake().ChangeDirection(
            Snake::Direction::kRight, Snake::Direction::kLeft);
        break;
    case Command::UP:
        game_state.GetSnake().ChangeDirection(
            Snake::Direction::kUp, Snake::Direction::kDown);
        break;
    case Command::DOWN:
        game_state.GetSnake().ChangeDirection(
            Snake::Direction::kDown, Snake::Direction::kUp);
        break;
    }
    game_state.UpdateGame();
}

void GameScene::Render(Renderer &renderer, GameState &game_state)
{
    const Snake &snake = game_state.GetSnake();
    const SDL_Point &food = game_state.GetFood();
    Level *current_level = game_state.GetCurrentLevel();
    // void Renderer::Render(Snake const snake, SDL_Point const &food) {
    SDL_Rect block;
    block.w = renderer.screen_width / renderer.grid_width;
    block.h = renderer.screen_height / renderer.grid_height;

    // Clear screen
    SDL_SetRenderDrawColor(renderer.GetSdlRenderer(), 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(renderer.GetSdlRenderer());

    // Render level (gray)
    SDL_SetRenderDrawColor(renderer.GetSdlRenderer(), 175, 175, 175, 255);
    std::vector<int> obstacle_indices =
        current_level->GetIndicesByGridContent().at(GridContent::OBSTACLE);
    for (int index : obstacle_indices)
    {
        int x = GetXFromIndex(index, renderer.grid_width);
        int y = GetYFromIndex(index, renderer.grid_width);
        block.x = x * block.w;
        block.y = y * block.h;
        SDL_RenderFillRect(renderer.GetSdlRenderer(), &block);
    }

    // Render food (yellow)
    SDL_SetRenderDrawColor(renderer.GetSdlRenderer(), 0xFF, 0xCC, 0x00, 0xFF);
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(renderer.GetSdlRenderer(), &block);

    // Render snake's body (white)
    SDL_SetRenderDrawColor(renderer.GetSdlRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const &point : snake.body)
    {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(renderer.GetSdlRenderer(), &block);
    }

    // Render snake's head
    block.x = static_cast<int>(snake.head_x) * block.w;
    block.y = static_cast<int>(snake.head_y) * block.h;
    if (snake.alive)
    {
        // Blue.
        SDL_SetRenderDrawColor(
            renderer.GetSdlRenderer(), 0x00, 0x7A, 0xCC, 0xFF);
    }
    else
    {
        // Red.
        SDL_SetRenderDrawColor(
            renderer.GetSdlRenderer(), 0xFF, 0x00, 0x00, 0xFF);
    }
    SDL_RenderFillRect(renderer.GetSdlRenderer(), &block);

    // Update Screen
    SDL_RenderPresent(renderer.GetSdlRenderer());
}
