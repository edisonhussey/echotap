
#include "Game_Session.h"
#include "Beatmap.h"
#include "Audio_Manager.h"
#include "Renderer.h"
#include "Animations.h"
#include <iostream>
#include "context.h"


Game_Session::Game_Session(context* context)
    : ctx(context)
{

}


void Game_Session::init() {
    if (!ctx || !ctx->beatmap || !ctx->audio_manager || !ctx->renderer) {
        std::cerr << "Error: Game_Session context or beatmap is not initialized." << std::endl;
        return;
    }

    // Initialize game session variables
    total_Score = 0.0f;
    combo = 0;
    max_combo = 0;

    // Add initialization text animation

    // Additional initialization logic can go here
}

void Game_Session::click_x_y(float x, float y, float time) {
    // Narrow down taps to a ±0.5s window around 'time' to reduce search
    float window_start = time - 2.0f;
    float window_end = time + 2.0f;



    if (!ctx || !ctx->beatmap || !ctx->audio_manager || !ctx->renderer) {
        std::cerr << "Error: Game_Session context or beatmap is not initialized." << std::endl;
        return;
    }
    
    std::vector<std::reference_wrapper<Tap>> taps_in_window = ctx->beatmap->get_taps_in_window_reference(window_start, window_end);

    for (int i=taps_in_window.size()-1;i>=0;i--){

        Tap& tap = taps_in_window[i].get();
        float map_click_distance = tap.size * 0.4f;

        float diff = std::abs(tap.perfect_hit_time - time);

        float distance_from_center = std::sqrt(
            std::pow(tap.x - x, 2) + std::pow(tap.y - y, 2)
        );

        if (tap.is_correct && diff <= 0.5f && tap.actual_hit_time < 0 && distance_from_center < map_click_distance) { // Check if within 0.5s and not already hit
            printf("Tap hit at time: %.2f, expected: %.2f, diff: %.2f\n", time, tap.perfect_hit_time, diff);


            float score = grader(tap.end_window - tap.start_window, diff);

            tap.score = score; //Set the score based on grading function
            total_Score += score; // Update total score
            combo++; // Increment combo count

            if (combo > max_combo) {
                max_combo = combo; // Update max combo if current is greater
            }

            tap.actual_hit_time = time; // Set actual hit time
            ctx->audio_manager->play("assets/audio/click_sounds/hat.wav", 1.0f); // Play hit sound
            // tap.color = {0, 255, 0, 255}; // Change color to green on hit // 


            // ctx->renderer->simple_render_text(
            //     tap.x, tap.y, std::to_string(tap.score), 0.8f, Color(0, 255, 0, 100)
            // ); // Render hit text

            ctx->animations->add_animation(
                std::make_unique<Text_Fade>(
                    ctx->renderer, ctx->game_time, (ctx->game_time)+2, tap.x, tap.y,
                    std::to_string(tap.score), 0.6f, Color(0, 170, 0, 100)

                )
            ); // Add hit text animation
            return;
        }

    }


    total_Score-= 50;
    combo = 0; // Reset combo on miss

    ctx->animations->add_animation(
        std::make_unique<Text_Fade>(
            ctx->renderer, ctx->game_time, (ctx->game_time)+2, x, y,
            "Miss", 0.4f, Color(255, 0, 0, 100)
        )
    ); // Add miss text animation



}



int Game_Session::grader(float abs_plus_minus_hit_window, float time_difference) {
    // Calculate the difference between the perfect hit time and the actual hit time
    if (time_difference < abs_plus_minus_hit_window * 0.1f) {
        return 100; // Perfect hit
    } else if (time_difference < abs_plus_minus_hit_window * 0.2f) {
        return 80; // Good hit
    } else if (time_difference < abs_plus_minus_hit_window * 0.3f) {
        return 50; // Okay hit
    } else if (time_difference < abs_plus_minus_hit_window * 0.5f) {
        return 20; // Bad hit
    } else {
        return 0; // Miss
    }
  
}



