#include <chrono>
#include <iostream>
#include <thread>

#include "SDL.h"

#include "auto_saver.h"
#include "controller.h"
#include "level.h"
#include "renderer.h"
#include "scene.h"
#include "scene_manager.h"
#include "shared_queue.h"
#include "types.h"

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
  std::cout << "Levels loaded" << "\n";

  SharedQueue<SaveData> save_queue;
  std::thread auto_save_thread(WatchForSaves, std::ref(save_queue));

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  GameState state(kGridWidth, kGridHeight, levels, save_queue);

  SceneManager scene_manager;
  scene_manager.Run(controller, state, renderer, kMsPerFrame);

  // Cleanup.
  save_queue.close();
  auto_save_thread.join();

  std::cout << "Game has terminated successfully!\n";
  std::cout << "Latest Score: " << state.GetScore() << "\n";
  return 0;
}
