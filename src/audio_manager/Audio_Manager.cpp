


#define MINIAUDIO_IMPLEMENTATION
#include "../../dependencies/miniaudio.h"  // adjust path as needed
#include "Audio_Manager.h"
#include <iostream>

Audio_Manager::Audio_Manager() : initialized(false) {}

Audio_Manager::~Audio_Manager() {
    cleanup();
    if (initialized) {
        ma_engine_uninit(&engine);
        initialized = false;
    }
}

bool Audio_Manager::init() {
    ma_result result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        std::cerr << "Failed to initialize audio engine\n";
        return false;
    }
    initialized = true;
    return true;
}

bool Audio_Manager::load(const std::string& path) {
    if (!initialized) {
        std::cerr << "Audio_Manager not initialized!\n";
        return false;
    }
    if (sounds.find(path) != sounds.end()) {
        // Already loaded
        return true;
    }

    ma_sound* sound = new ma_sound;
    ma_result result = ma_sound_init_from_file(&engine, path.c_str(), 0, NULL, NULL, sound);
    if (result != MA_SUCCESS) {
        std::cerr << "Failed to load sound: " << path << "\n";
        delete sound;
        return false;
    }

    sounds[path] = sound;
    return true;
}

void Audio_Manager::play(const std::string& path, float volume) {
    if (!initialized) {
        std::cerr << "Audio_Manager not initialized!\n";
        return;
    }

    auto it = sounds.find(path);
    if (it == sounds.end()) {
        std::cerr << "Sound not loaded: " << path << "\n";
        return;
    }

    ma_sound* sound = it->second;
    ma_sound_set_volume(sound, volume);
    ma_sound_start(sound);
}

void Audio_Manager::cleanup() {
    for (auto& kv : sounds) {
        ma_sound_uninit(kv.second);
        delete kv.second;
    }
    sounds.clear();
}
