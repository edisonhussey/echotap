// #ifndef AUDIO_MANAGER_H
// #define AUDIO_MANAGER_H

// #include <string>
// #include <unordered_map>
// #include <memory>
// #include "../../dependencies/miniaudio.h"

// class Audio_Manager {
// public:
//     Audio_Manager();
//     ~Audio_Manager();

//     bool init();
//     bool load(const std::string& path);
//     void play(const std::string& path);
//     void cleanup();

// private:
//     ma_engine engine;
//     bool initialized = false;
//     std::unordered_map<std::string, ma_sound> sounds;
// };

// #endif // AUDIO_MANAGER_H


// In Audio_Manager.h
// #include <map>
// #include <string>
// #include "../../dependencies/miniaudio.h"

// class Audio_Manager {
// public:
//     Audio_Manager();
//     ~Audio_Manager();

//     bool init();
//     bool load(const std::string& path);
//     // void play(const std::string& path);
//     void play(const std::string& path, float volume = 1.0f);

//     void cleanup();

// private:
//     ma_engine engine;
//     bool initialized = false;
//     std::map<std::string, ma_sound*> sounds;
// };


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
