
#include "Game_Session.h"
#include "Beatmap.h"
#include "Audio_Manager.h"
#include <iostream>

Game_Session::Game_Session(Beatmap* bm, Audio_Manager* audio)
    : beatmap(bm), audio_manager(audio) {}



void Game_Session::click_x_y(float x, float y, float time) {
    // Narrow down taps to a ±0.5s window around 'time' to reduce search
    float window_start = time - 2.0f;
    float window_end = time + 2.0f;



    std::vector<std::reference_wrapper<Tap>> taps_in_window = beatmap->get_taps_in_window_reference(window_start, window_end);

    for (int i=taps_in_window.size()-1;i>=0;i--){

        

        Tap& tap = taps_in_window[i].get();
        float map_click_distance = tap.size * 0.4f;

        float diff = std::abs(tap.perfect_hit_time - time);

        float distance_from_center = std::sqrt(
            std::pow(tap.x - x, 2) + std::pow(tap.y - y, 2)
        );

        if (tap.is_correct && diff <= 0.5f && tap.actual_hit_time < 0 && distance_from_center < map_click_distance) { // Check if within 0.5s and not already hit
            printf("Tap hit at time: %.2f, expected: %.2f, diff: %.2f\n", time, tap.perfect_hit_time, diff);
            tap.actual_hit_time = time; // Set actual hit time
            audio_manager->play("assets/audio/click_sounds/hat.wav", 1.0f); // Play hit sound
            tap.color = {0, 255, 0, 255}; // Change color to green on hit
            break;
        }
    }
}




