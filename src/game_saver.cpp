#include "game_saver.h"

#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "types.h"

GameSaver::GameSaver(
    SaveData save,
    std::filesystem::path save_path,
    std::size_t max_num_saves)
    : save(save),
      save_path(save_path),
      max_num_saves(max_num_saves) {}

void GameSaver::Save()
{
    std::deque<std::string> save_lines = ReadExistingSaveIfExists();
    std::cout << "Number of existing lines: " << save_lines.size() << "\n";
    save_lines.push_front(GetNewSaveLine());
    // Remove the oldest saves until the number of save lines equals max
    // save lines.
    while (save_lines.size() > max_num_saves)
    {
        std::cout << "Too many saves: Removing one." << "\n";
        save_lines.pop_back();
    }
    std::cout << "Final number of saves: " << save_lines.size() << "\n";
    WriteSaveFile(save_lines);
}

std::deque<std::string> GameSaver::ReadExistingSaveIfExists()
{
    std::ifstream file(save_path);
    if (!file)
    {
        return std::deque<std::string>();
    }

    return ReadLinesFromFile(file);
}

std::deque<std::string> GameSaver::ReadLinesFromFile(std::ifstream &file)
{
    std::deque<std::string> existing_lines;

    std::string fileLine;
    size_t numLinesRead{0};
    while (getline(file, fileLine))
    {
        if (fileLine.size() == 0)
        {
            continue;
        }
        numLinesRead++;
        if (numLinesRead > max_num_saves)
        {
            std::cout << "Too many lines to read in save file. Stopping at " << existing_lines.size() << "\n";
            break;
        }
        existing_lines.push_back(fileLine);
    }

    return existing_lines;
}

std::string GameSaver::GetNewSaveLine()
{
    std::ostringstream os;
    os << save.date_time << " | " << save.level_name << " | " << save.score;
    return os.str();
}

void GameSaver::WriteSaveFile(std::deque<std::string> save_lines)
{
    std::ofstream file(save_path);
    for (std::string line : save_lines)
    {
        file << line << "\n";
    }
}
