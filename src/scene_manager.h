#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "controller.h"
#include "scene.h"
#include "types.h"

// Top-level class that manages all Scenes.
class SceneManager
{
public:
    SceneManager();
    // Checks if the current Command and Scene warrants a Scene change, and
    // makes any necessary changes to GameState on Scene change.
    void CheckSceneTransition(GameState &game_state);
    // Changes the current scene.
    void ChangeScene(Scene *new_scene);
    // Runs the game loop.
    void Run(Controller const &controller,
             GameState &game_state,
             Renderer &renderer,
             std::size_t target_frame_duration);

private:
    GameScene game_scene;
    LevelScene level_scene;

    Scene *current_scene;
};

#endif
