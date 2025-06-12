


#include "Audio_Manager.h"
#include "Input_Manager.h"
#include "Game_Session.h"
#include "detect_beats.h"

#include "Beatmap.h"
#include "Tap.h"
#include "Prompt.h"

#include "Map_Generator.h"
#include "Renderer.h"

#include <thread>
#include <chrono>
#include <iostream>


#include <GLFW/glfw3.h>

int main() {
   

    Audio_Manager audio;
    if (!audio.init()) return -1;

    std::string musicPath = "assets/audio/songs/going_crazy.wav";
    std::string clickPath = "assets/audio/click_sounds/hat.wav";

    if (!audio.load(clickPath)) return -1;
    if (!audio.load(musicPath)) return -1;

    std::vector<float> beats = detect_beats(musicPath, 0.7f);

    Map_Generator generator;

    Quiz quiz;

    for (int i = 1; i <= 10; ++i) {
        std::string prompt = "Question " + std::to_string(i);
        std::vector<std::string> choices = {
            "Option A", "Option B", "Option C", "Option D"
        };
        quiz.add_question(prompt, choices);
    }



    Beatmap beatmap = generator.create_map(
        0.5f, 0.7f,
        "assets/images/backgrounds/beatmap_background.png",
        musicPath, quiz
    );


    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    Renderer renderer(1280, 720);
    if (!renderer.init()) return -1;

    renderer.initBackground("assets/images/backgrounds/beatmap_background.png");


    Game_Session game_session(&beatmap, &audio);
    
    

    Input_Manager input_manager(renderer.get_window(), &audio);

    input_manager.set_game_session(&game_session); //links game session to input manager


    audio.play(musicPath, 0.1f); // start music

    float startTime = glfwGetTime();
    float lastClickTime = 0.0f;
    size_t beatIndex = 0;

    while (!renderer.should_close()) {
        input_manager.Update();
        input_manager.Handle_Inputs();

        float currentTime = glfwGetTime() - startTime;

        // Play click sounds at beat times
        if (beatIndex < beats.size() && currentTime >= beats[beatIndex]) {
            // audio.play(clickPath, 1.0f);
            lastClickTime = beats[beatIndex];
            beatIndex++;
        }

        renderer.render(beatmap, currentTime);
    }

    return 0;
}

