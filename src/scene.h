#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include "game_state.h"
#include "renderer.h"
#include "types.h"

#include <utility>

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
