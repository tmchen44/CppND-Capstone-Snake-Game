#include <deque>
#include <filesystem>

#include "types.h"

class GameSaver
{
public:
    GameSaver(SaveData save,
              std::filesystem::path save_path,
              std::size_t max_num_saves);
    void Save();

private:
    // Returns a deque with existing lines (should be most recent first) from
    // the save_path, if the file exists. Otherwise, returns an empty deque.
    std::deque<std::string> ReadExistingSaveIfExists();

    // Reads existing lines from the file, up to the maximum number of saves.
    std::deque<std::string> ReadLinesFromFile(std::ifstream &file);

    // Gets a formatted string from SaveData.
    std::string GetNewSaveLine();

    // Writes the given save lines to the save file.
    void WriteSaveFile(std::deque<std::string> save_lines);

    const SaveData save;
    const std::filesystem::path save_path;
    const std::size_t max_num_saves;
};
