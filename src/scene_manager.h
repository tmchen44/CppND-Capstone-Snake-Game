#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "controller.h"
#include "scene.h"
#include "types.h"

#include <exception>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// Top-level class that manages all Scenes.
class SceneManager
{
public:
    SceneManager();
    // Behavioral methods
    void CheckSceneTransition(GameState &game_state);
    void ChangeScene(Scene *new_scene);
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
