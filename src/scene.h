#ifndef SCENE_H
#define SCENE_H

#include <utility>

#include "game_state.h"
#include "renderer.h"
#include "types.h"

class Scene
{
public:
    virtual void StoreCommand(Command command) final { _command = command; }
    virtual Command GetCommand() final { return _command; }
    virtual void Update(GameState &game_state) = 0;
    virtual void Render(Renderer &renderer, GameState &game_state) = 0;
    virtual SceneName GetSceneName() = 0;

private:
    Command _command = Command::NONE;
};

class LevelScene : public Scene
{
public:
    SceneName GetSceneName() override;
    void Update(GameState &game_state) override;
    void Render(Renderer &renderer, GameState &game_state) override;
};

class GameScene : public Scene
{
public:
    SceneName GetSceneName() override;
    void Update(GameState &game_state) override;
    void Render(Renderer &renderer, GameState &game_state) override;
};

#endif
