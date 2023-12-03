#ifndef LEVEL_H
#define LEVEL_H

#include "types.h"

#include <exception>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Level
{
public:
    // Getters/setters

    // Returns flattened representation of the Level.
    std::vector<GridContent> AsFlattened() { return _flattened; }
    // Gets mapping from GridContent to indices with that GridContent.
    std::unordered_map<GridContent, std::vector<int>>
    GetIndicesByGridContent() { return _indices_by_grid_content; }

    // Behavioral methods

    void InitLevel(
        std::string name,
        Dimension level_dimensions,
        std::vector<GridContent> &parsed_level);

private:
    void SetIndicesByGridContent();

    // Level name.
    std::string _name;
    // Dimensions of the level.
    Dimension _dimensions;
    // Flattened representation of the level grid.
    std::vector<GridContent> _flattened;
    // mapping of GridContent to a vector of indices identifying that
    // GridContent's locations within _flattened.
    std::unordered_map<GridContent, std::vector<int>> _indices_by_grid_content;
};

class LevelLoader
{
public:
    LevelLoader(size_t game_height, size_t game_width)
        : _game_dimensions{game_height, game_width} {}

    std::vector<std::unique_ptr<Level>> LoadLevelsFromDirectory(
        std::string directory_path);
    std::unique_ptr<Level> LoadLevelFromFile(std::filesystem::path level_path);

private:
    // Game dimensions for validating if the level is compatible with game.
    Dimension _game_dimensions;

    std::vector<GridContent> GetParsedLevel(std::ifstream &file);
};

#endif
