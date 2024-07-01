#ifndef LEVEL_H
#define LEVEL_H

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "types.h"

class Level
{
public:
    // Getters/setters
    std::string GetName() { return _name; }

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
    LevelLoader(std::size_t game_width, std::size_t game_height)
        : _game_dimensions{game_width, game_height} {}

    std::vector<std::unique_ptr<Level>> LoadLevelsFromDirectory(
        std::filesystem::path directory_path);
    std::unique_ptr<Level> LoadLevelFromFile(std::filesystem::path level_path);

private:
    // Game dimensions for validating if the level is compatible with game.
    Dimension _game_dimensions;

    std::vector<GridContent> GetParsedLevel(std::ifstream &file);
};

#endif
