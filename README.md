# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
<!-- * SDL_ttf >= 2.0.15
  * Linux: Listed in Debian package manager as libsdl2-ttf-dev -->

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Basic Game Operation

The game has been extended so that there are now two "scenes" - a level select scene and the actual snake game scene. There is currently no on-screen text yet, so one will need to follow the instructions here. In short, the level select scene does not show the snake or food, just the levels, and the snake game scene will show the snake and food. Detailed instructions below:
* The game always starts with the level select scene. Here you can use arrow keys to view the various levels available for play. Pressing ENTER will start a game using the currently viewed level. Pressing ESC will "return" to the existing game (on startup, this will be a new game on the first level).
* While in the snake game scene, the arrow keys control the snake. Pressing ESC during a game will bring you back to the level select scene. If you press ESC again from the level select scene, you will be brought back to the original game. If you press ENTER from the level select scene, it will start a new game using the currently viewed level.
* The game features auto-saving of game results. The auto-save feature only records the results of a game after the snake dies. If you press ESC and start a new game without the snake dying, or if you QUIT a game before the snake dies, the result of that previous game will **not** be saved.
* The snake now dies if it runs into itself or if it runs into the level obstacles colored in gray.

## Adding Custom Levels

The game has also been extended to allow for custom levels. These can be defined as .txt files within the `assets/levels` directory. Some points to note:
* The `#` character uniquely represents an obstacle that the snake must avoid. All other characters (empty space, `.`, etc.) refer to an open, non-obstacle space.
* The text file **must** follow the in-game grid width and height, which is currently defined in `main.cpp` as 32 characters by 32 characters.
* Currently, the snake automatically starts in the "center middle" of the level, so if that spot is occupied by a `#` obstacle character in your custom level, that level probably won't be playable, as the snake will instantly die when starting that level. Ideally, on game startup, we would place the snake to avoid the obstacles (just like we place the food to avoid the snake and obstacles), but this is not supported yet.

## New features

The new features added to the base game have been briefly mentioned in the above sections. They will now be listed in detail below:

1. The game now supports different "scenes" besides the actual snake game. Currently, besides the actual snake game, only a level select scene exists. But one could imagine other scenes being added, e.g. a high score scene or an options scene.
2. Players can add their own custom levels (represented by text files), which can place obstacles almost anywhere in the 32 by 32 game grid. The food placement algorithm has been updated to not only avoid placing food on the snake itself but also avoid placing food on one of the level obstacles.
3. Whenever the snake dies (a game "properly" finishes), the results are saved to a text file, which keeps track of the ten latest game results.

## Rubric points addressed

See each sub-section below (corresponding to each of the rubric sections) for details regarding which rubric points are addressed (and location in code):

### Compiling and Testing (All Rubric Points REQUIRED)

Assuming all dependencies have been installed, the code will compile and run according to the build instructions section above. Please note that the game carries out file directory operations that are specific to Linux, so the game probably will only run correctly in a Linux environment.

### Loops, Functions, I/O - meet at least 2 criteria

1. The project demonstrates an understanding of C++ functions and control structures.
    * This can be seen in various files: e.g. `level.cpp`, `auto_saver.cpp`, `scene.cpp`.
2. The project reads data from a file and process the data, or the program writes data to a file.
    * This can ben seen in `level.cpp` (`LevelLoader::LoadLevelFromFile`, line 69)
    * This can also be seen in `game_saver.cpp` (`GameSaver::ReadExistingSaveIfExists`, line 34; `GameSaver::WriteSaveFile`, line 76)
3. The project accepts user input and processes the input.
    * There is a level select scene, which processes input differently from the snake game scene. There is a new keyboard command abstraction called `Command` (located in `types.h`, line 32). The new level select `Command`s are processed in `scene.cpp` (`LevelScene::Update`, line 9).
4. The project uses data structures and immutable variables.
    * This can be seen in various places. E.g. `level.cpp` (`Level::LoadLevesFromDirectory`, line 47), `shared_queue.h` (line 70), and `main.cpp` (lines 25-26).
  
### Object Oriented Programming - meet at least 3 criteria

1. One or more classes are added to the project with appropriate access specifiers for class members.
    * See `shared_queue.h`, `scene.h`, `level.h`, all of which contain new classes with access specifiers.
2. Class constructors utilize member initialization lists.
    * See `game_saver.cpp` (`GameSaver::GameSaver`, line 10).
    * See `scene_manager.cpp` (`SceneManager::SceneManager`, line 5)
3. Classes abstract implementation details from their interfaces.
    * See `scene_manager.h` and `shared_queue.h`
4. Classes follow an appropriate inheritance hierarchy with virtual and override functions.
    * See `scene.h`
5. Templates generalize functions or classes in the project.
    * See `shared_queue.h`

### Memory Management - meet at least 3 criteria

1. The project makes use of references in function declarations.
    * See `level.h` (`Level::InitLevel`, line 28; `Level::GetParsedLevel`, line 58)
    * See `auto_saver.h` (`WatchForSaves`, line 12)
2. The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
    * See `shared_queue.h`, where resources shared between threads are enclosed/managed entirely within a class and its members.
    * See `scene_manager.cpp`, where Scene instances are managed within the scope of SceneManager.
3. The project uses move semantics to move data instead of copying it, where possible.
    * See `game_state.cpp` (`GameState::CheckSnakeCollision`, line 75)
    * See `level.cpp` (`LevelLoader::LoadLevelsFromDirectory`, line 55)`
    * See `shared_queue.h` (`SharedQueue::push`, line 29)`
4. The project uses smart pointers instead of raw pointers.
    * See `level.cpp` (`LevelLoader::LoadLevelFromFile`, line 77)

### Concurrency - meet at least 2 criteria

1. The project uses multithreading.
    * See `main.cpp` (lines 35, 49), where a child thread is spawned to watch for incoming SaveData and save it to a text file while the parent thread runs the actual game.
2. A promise and future is used in the project.
    * See `level.cpp` (`LevelLoader::LoadLevelsFromDirectory`), where std::async and std::future are used to load levels asynchronously.
3. A mutex or lock is used in the project.
    * See `shared_queue.h` (lines 68, 26, 37, 60), where a mutex and appropriate locks are used to guard against race conditions that would arise during the reading or modifying of shared resources.
4. A condition variable is used in the project.
    * See `shared_queue.h` (lines 69, 31, 38, 64), where a condition variable is used to signal resource availability to threads.

## CC Attribution-ShareAlike 4.0 International

Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
