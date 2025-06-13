

#pragma once


#include "Beatmap.h"
#include "Audio_Manager.h"
#include <vector>
#include "Renderer.h"


class Game_Session{

    private:
        // Add private members here if needed
        Beatmap* beatmap; // Pointer to the Beatmap object
        Audio_Manager* audio_manager; // Pointer to the Audio_Manager object
        Renderer* renderer; // Pointer to the Renderer object
        Animations animations; // Animations object for rendering animations

        float total_Score = 0.0f; // Total score for the game session
        int combo = 0; // Current combo count
        int max_combo = 0; // Maximum combo achieved in the session

        void link_beatmap(Beatmap* bm);
        void link_audio(Audio_Manager* audio);
        void link_renderer(Renderer* renderer);
        void link_animations(Animations* animations);

    public:
        explicit Game_Session(Beatmap* bm, Audio_Manager* audio, Renderer* renderer, Animations* animations);
        
        ~Game_Session() = default;

        void click_x_y(float x, float y, float time);
        int grader(float abs_plus_minus_hit_window, float time_difference);

};