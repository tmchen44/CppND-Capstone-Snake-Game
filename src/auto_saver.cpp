#include "auto_saver.h"

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include "exceptions.h"
#include "game_saver.h"

// Maximum number of saves to keep in the save file.
const std::size_t MAX_NUM_SAVES{10};

void WatchForSaves(
    SharedQueue<SaveData> &queue, std::filesystem::path save_path)
{
    while (true)
    {
        SaveData save;
        try
        {
            save = queue.next();
        }
        catch (const QueueClosedAndEmptyException &e)
        {
            // Queue is closed and empty. No need to watch for saves anymore.
            std::cout << "Closing watcher." << "\n";
            break;
        }
        std::cout << "Saving " << save.date_time << "\n";
        GameSaver(save, save_path, MAX_NUM_SAVES).Save();
        std::cout << save.date_time << " saved!" << "\n";
    }
}
