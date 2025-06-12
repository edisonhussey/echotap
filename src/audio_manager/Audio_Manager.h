

#pragma once

#include <string>
#include <unordered_map>
#include "../../dependencies/miniaudio.h"

struct Audio_Manager {
    Audio_Manager();
    ~Audio_Manager();

    bool init();
    bool load(const std::string& path);
    void play(const std::string& path, float volume = 1.0f);
    void cleanup();

private:
    ma_engine engine;
    bool initialized;
    std::unordered_map<std::string, ma_sound*> sounds;
};
