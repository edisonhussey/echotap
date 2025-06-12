

#pragma once


#include "Beatmap.h"
#include "Audio_Manager.h"
#include <vector>


class Game_Session{

    private:
        // Add private members here if needed
        Beatmap* beatmap; // Pointer to the Beatmap object
        Audio_Manager* audio_manager; // Pointer to the Audio_Manager object

        float total_Score = 0.0f; // Total score for the game session
        int combo = 0; // Current combo count
        int max_combo = 0; // Maximum combo achieved in the session
        



    public:
        explicit Game_Session(Beatmap* bm, Audio_Manager* audio);

        ~Game_Session() = default;

        void click_x_y(float x, float y, float time);

};