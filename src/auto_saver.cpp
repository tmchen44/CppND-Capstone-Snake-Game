#include "auto_saver.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "exceptions.h"

namespace
{
    // Finds existing save file or creates
    void SaveGame(SaveData save);
}

void WatchForSaves(SharedQueue<SaveData> &queue)
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
        SaveGame(save);
        std::cout << save.date_time << " saved!" << "\n";
    }
}

namespace
{
    void SaveGame(SaveData save) {}
}
