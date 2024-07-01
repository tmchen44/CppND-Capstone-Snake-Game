#ifndef AUTO_SAVER_H
#define AUTO_SAVER_H

#include <filesystem>

#include "shared_queue.h"
#include "types.h"

// Watches for SaveData coming into the SharedQueue, grabs one, and processes
// it. Continues until the channel is closed and empty.
void WatchForSaves(
    SharedQueue<SaveData> &queue,
    std::filesystem::path save_path);

#endif
