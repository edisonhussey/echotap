// #pragma once
// #include "Audio_Manager.h"
// #include "Renderer.h"
// #include "Game_Session.h"
// #include "Animations.h"
// #include "Beatmap.h"
// #include "Input_Manager.h"

// struct context {
//     Audio_Manager* audio_manager = nullptr;
//     Renderer* renderer = nullptr;
//     Game_Session* game_session = nullptr;
//     Animations* animations = nullptr;
//     Beatmap* beatmap = nullptr;
//     Input_Manager* input_manager = nullptr;
// };

// context.h
#pragma once

// Forward declarations
class Renderer;
class Animations;
class Input_Manager;
class Beatmap;
class Game_Session;
class Audio_Manager;

struct context {
    Renderer* renderer = nullptr;
    Animations* animations = nullptr;
    Input_Manager* input_manager = nullptr;
    Beatmap* beatmap = nullptr;
    Game_Session* game_session = nullptr;
    Audio_Manager* audio_manager = nullptr;
    float game_time = 0.0f; // Current time in seconds
};
