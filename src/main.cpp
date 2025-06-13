


#include "Audio_Manager.h"
#include "Input_Manager.h"
#include "Game_Session.h"
#include "detect_beats.h"

#include "Beatmap.h"
#include "Tap.h"
#include "Prompt.h"
#include "Animations.h"

#include "Map_Generator.h"
#include "Renderer.h"

#include <thread>
#include <chrono>
#include <iostream>


#include <GLFW/glfw3.h>


struct game_context {
    Audio_Manager* audio = nullptr;
    Renderer* renderer = nullptr;
    Game_Session* game_session = nullptr;
    Animations* animations = nullptr;
    Beatmap* beatmap = nullptr;
    Input_Manager* input_manager = nullptr;
};


int main() {
    game_context ctx;

    ctx.audio = new Audio_Manager(); //works fine alone 
    ctx.renderer = new Renderer(1280, 720); 
    ctx.animations = new Animations();
    ctx.beatmap = new Beatmap({}, {}); // Initialize with empty vectors
    ctx.input_manager = new Input_Manager(ctx.renderer->get_window(), ctx.audio);
    ctx.game_session = new Game_Session(ctx.beatmap, ctx.audio, ctx.renderer, ctx.animations);

    ctx.input_manager->set_game_session(ctx.game_session); // Link game session to input manager



    // Audio_Manager audio;
    // if (!audio.init()) return -1;

    // std::string musicPath = "assets/audio/songs/going_crazy.wav";
    // std::string clickPath = "assets/audio/click_sounds/hat.wav";

    // if (!audio.load(clickPath)) return -1;
    // if (!audio.load(musicPath)) return -1;

    // std::vector<float> beats = detect_beats(musicPath, 0.7f);

    // Map_Generator generator;

    // Quiz quiz;

    // for (int i = 1; i <= 10; ++i) {
    //     std::string prompt = "Question " + std::to_string(i);
    //     std::vector<std::string> choices = {
    //         "Option A", "Option B", "Option C", "Option D"
    //     };
    //     quiz.add_question(prompt, choices);
    // }



    // Beatmap beatmap = generator.create_map(
    //     0.5f, 0.7f,
    //     "assets/images/backgrounds/beatmap_background.png",
    //     musicPath, quiz
    // );


    // if (!glfwInit()) {
    //     std::cerr << "Failed to initialize GLFW" << std::endl;
    //     return -1;
    // }
    // Renderer renderer(1280, 720);
    // if (!renderer.init()) return -1;

    // renderer.initBackground("assets/images/backgrounds/beatmap_background.png");

 
    

    // Game_Session game_session(&beatmap, &audio);
    
    

    // Input_Manager input_manager(renderer.get_window(), &audio);

    // input_manager.set_game_session(&game_session); //links game session to input manager


    // audio.play(musicPath, 0.1f); // start music

    // Animations animations;
    // animations.add_animation(std::make_unique<Text_Fade>(&renderer, 4.0f, 15.0f, 0.5f, 0.5f,
    //     "Click to start!", 0.5f, Color(122, 122, 122)));

    // float startTime = glfwGetTime();
    // float lastClickTime = 0.0f;
    // size_t beatIndex = 0;

    // while (!renderer.should_close()) {
    //     input_manager.Update();
    //     input_manager.Handle_Inputs();

    //     float currentTime = glfwGetTime() - startTime;

    //     // Play click sounds at beat times
    //     // if (beatIndex < beats.size() && currentTime >= beats[beatIndex]) {
    //     //     // audio.play(clickPath, 1.0f);
    //     //     lastClickTime = beats[beatIndex];
    //     //     beatIndex++;
    //     //     // audio.play(clickPath, 1.0f);
    //     // }
        
    //     renderer.render(beatmap, currentTime, animations);

    //     animations.update(currentTime);
    //     // animations.render(renderer, currentTime);
    //     // animations.remove_finished_animations();
    //     // animations.remove_finished_animations();
    // }

    // return 0;
}

