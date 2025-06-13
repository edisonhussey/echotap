

#pragma once


#include "Beatmap.h"
#include "Audio_Manager.h"
#include <vector>
#include "Renderer.h"
#include "context.h"


class Game_Session{

    public:
        explicit Game_Session(context* ctx);

        ~Game_Session() = default;

        void click_x_y(float x, float y, float time);
        int grader(float abs_plus_minus_hit_window, float time_difference);

        void init();

        float total_Score = 0.0f; // Total score for the game session
        int combo = 0; // Current combo count
        int max_combo = 0; // Maximum combo achieved in the session

    private:
        context* ctx;

        

        // void link_beatmap(Beatmap* bm);
        // void link_audio(Audio_Manager* audio);
        // void link_renderer(Renderer* renderer);
        // void link_animations(Animations* animations);

    

};