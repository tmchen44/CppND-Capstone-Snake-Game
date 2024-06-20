#include "types.h"
#include "scene_manager.h"

SceneManager::SceneManager()
    : game_scene(),
      level_scene()
{
    current_scene = &level_scene;
}

void SceneManager::CheckSceneTransition(GameState &game_state)
{
    SceneName scene_name = current_scene->GetSceneName();
    Command command = current_scene->GetCommand();
    if (command == Command::QUIT)
    {
        game_state.StopGame();
    }
    else if (scene_name == SceneName::LEVEL && command == Command::ENTER)
    {
        // Reset game and play new level.
        game_state.SetViewLevelAsCurrentLevel();
        game_state.ResetViewIndex();
        game_state.ResetGame();
        ChangeScene(&game_scene);
    }
    else if (scene_name == SceneName::LEVEL && command == Command::ESCAPE)
    {
        // Go back to game without changes.
        game_state.ResetViewIndex();
        ChangeScene(&game_scene);
    }
    else if (scene_name == SceneName::GAME && command == Command::ESCAPE)
    {
        // Go to menu.
        ChangeScene(&level_scene);
    }
}

void SceneManager::ChangeScene(Scene *new_scene)
{
    // Always set current command to NONE when replacing the scene.
    current_scene->StoreCommand(Command::NONE);
    current_scene = new_scene;
}

void SceneManager::Run(Controller const &controller,
                       GameState &game_state,
                       Renderer &renderer,
                       std::size_t target_frame_duration)
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;

    while (game_state.IsRunning())
    {
        frame_start = SDL_GetTicks();

        // Input, Update, Render - the main game loop.
        controller.HandleInput(current_scene);
        CheckSceneTransition(game_state);
        current_scene->Update(game_state);
        current_scene->Render(renderer, game_state);
        // Clear command at end of cycle.
        current_scene->StoreCommand(Command::NONE);

        frame_end = SDL_GetTicks();

        // Keep track of how long each loop through the input/update/render cycle
        // takes.
        frame_count++;
        frame_duration = frame_end - frame_start;

        // After every second, update the window title.
        if (frame_end - title_timestamp >= 1000)
        {
            renderer.UpdateWindowTitle(game_state.GetScore(), frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration is
        // smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < target_frame_duration)
        {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}
