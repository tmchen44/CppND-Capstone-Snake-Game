#include "exceptions.h"
#include "level.h"

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <memory>
#include <string>

// Asserts parsed representation with dimensions and additional initialization.
void Level::InitLevel(
    std::string name,
    Dimension level_dims,
    std::vector<GridContent> &parsed_level)
{
    // Assert Level has not been initialized already.
    assert(_flattened.size() == 0);
    // Assert given parse size corresponds with given height and width.
    assert(parsed_level.size() == level_dims.height * level_dims.width);
    _name = name;
    _dimensions = level_dims;
    _flattened = parsed_level;

    SetIndicesByGridContent();
}

// Builds mapping from GridContent to vector of indexes for that particular
// GridContent.
void Level::SetIndicesByGridContent()
{
    _indices_by_grid_content = {
        {GridContent::EMPTY, std::vector<int>()},
        {GridContent::OBSTACLE, std::vector<int>()},
    };

    for (size_t i = 0; i < _flattened.size(); ++i)
    {
        _indices_by_grid_content[_flattened[i]].push_back(i);
    }
}

// Creates Levels from the Level text files in a directory.
std::vector<std::unique_ptr<Level>>
LevelLoader::LoadLevelsFromDirectory(std::string path)
{
    std::vector<std::future<std::unique_ptr<Level>>> futures;
    for (const auto &dir_value : std::filesystem::directory_iterator(path))
    {
        auto level_future =
            std::async(&LevelLoader::LoadLevelFromFile, this, dir_value.path());

        futures.emplace_back(std::move(level_future));
    }
    std::vector<std::unique_ptr<Level>> levels;

    for (auto &future : futures)
    {
        levels.emplace_back(future.get());
    }

    return levels;
}

// Creates Level from the Level text file specified in the path.
std::unique_ptr<Level>
LevelLoader::LoadLevelFromFile(std::filesystem::path level_path)
{
    std::ifstream file(level_path);
    if (!file)
    {
        throw CannotOpenFileException(level_path);
    }
    std::vector<GridContent> parsed = GetParsedLevel(file);
    auto l = std::make_unique<Level>();
    std::cout << "Initializing " << level_path.stem().string() << std::endl;
    l->InitLevel(level_path.stem().string(), _game_dimensions, parsed);
    return l;
}

// Validates and parses file into flattened vector of GridContent.
std::vector<GridContent> LevelLoader::GetParsedLevel(std::ifstream &file)
{
    std::vector<GridContent> parsed;
    std::string fileLine;
    size_t numLines{0};
    while (getline(file, fileLine))
    {
        numLines++;
        if (fileLine.size() != _game_dimensions.width)
        {
            throw IncorrectLevelDimensionsException(
                "width", _game_dimensions.width, fileLine.size());
        }

        for (char c : fileLine)
        {
            if (c == '#')
            {
                parsed.push_back(GridContent::OBSTACLE);
            }
            else
            {
                parsed.push_back(GridContent::EMPTY);
            }
        }
    }
    if (numLines != _game_dimensions.height)
    {
        throw IncorrectLevelDimensionsException(
            "height", _game_dimensions.height, numLines);
    }

    return parsed;
}
