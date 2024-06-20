#include <iostream>
#include "controller.h"
#include "level.h"
#include "renderer.h"
#include "scene.h"
#include "scene_manager.h"
#include "SDL.h"

int main()
{
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  const std::string kLevelDirectory{"../assets/levels"};

  LevelLoader loader(kGridWidth, kGridHeight);
  std::vector<std::unique_ptr<Level>> levels =
      loader.LoadLevelsFromDirectory(kLevelDirectory);

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  GameState state(kGridWidth, kGridHeight, levels);

  SceneManager scene_manager;
  scene_manager.Run(controller, state, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Latest Score: " << state.GetScore() << "\n";
  std::cout << "Latest Size: " << state.GetSize() << "\n";
  return 0;
}
