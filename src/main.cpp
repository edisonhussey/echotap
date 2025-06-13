


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
#include "context.h"

class Renderer;
class Audio_Manager;
class Game_Session;
class Animations;
class Input_Manager;
class Beatmap;




int main() {
    context ctx;

    ctx.audio_manager = new Audio_Manager(); // Initialize audio manager
    if (!ctx.audio_manager->init()) {

        std::cerr << "Failed to initialize audio manager." << std::endl;
        return -1;
    }
    
    ctx.renderer = new Renderer(1280, 720, &ctx); // required
    if (!ctx.renderer->init()) { //required
        std::cerr << "Failed to initialize renderer." << std::endl;
        return -1;
    }

    ctx.animations = new Animations(&ctx); // Initialize animations

    ctx.beatmap = new Beatmap({}, {}, &ctx); // Initialize with empty vectors

    ctx.input_manager = new Input_Manager(&ctx); // Initialize input manager

    ctx.game_session = new Game_Session(&ctx); // Initialize game session with context





    
    ctx.audio_manager->load("assets/audio/click_sounds/hat.wav"); // Load click sound
    ctx.audio_manager->load("assets/audio/songs/unshattered.wav"); // Load music file

    ctx.audio_manager->play("assets/audio/songs/unshattered.wav", 0.1f); // Start music
    ctx.renderer->initBackground("assets/images/backgrounds/beatmap_background.png"); // Initialize background
    ctx.animations->add_animation(std::make_unique<Text_Fade>(
        ctx.renderer, 4.0f, 15.0f, 0.5f, 0.5f,
        "Click to start!", 0.5f, Color(122, 122, 122)
    ));
    float startTime = glfwGetTime();
    float lastClickTime = 0.0f;
    size_t beatIndex = 0;
    std::string musicPath = "assets/audio/songs/unshattered.wav";
    std::string clickPath = "assets/audio/click_sounds/hat.wav";
    std::vector<float> beats = detect_beats(musicPath, 0.7f); // Detect beats from the music file
    Map_Generator generator; // Initialize map generator
    Quiz quiz; // Initialize quiz
    for (int i = 1; i <= 10; ++i) {
        std::string prompt = "Question " + std::to_string(i);
        std::vector<std::string> choices = {
            "Option A", "Option B", "Option C", "Option D"
        };
        quiz.add_question(prompt, choices); // Add questions to the quiz
    }
    auto [tappy,prompty] = generator.create_map(
        0.5f, 0.7f,
        "assets/images/backgrounds/beatmap_background.png",
        musicPath, quiz
    );// Create beatmap using the generator

    ctx.beatmap->setTaps(tappy); // Set taps in the beatmap
    ctx.beatmap->setPrompts(prompty); // Set prompts in the beatmap


    // if (!ctx.beatmap) {
    //     std::cerr << "Failed to create beatmap." << std::endl;
    //     return -1;
    // }
    // Main game loop
    // float previoius_time=0.0f;
    while (!ctx.renderer->should_close()) {
        ctx.input_manager->Update(); // Update input manager
        ctx.input_manager->Handle_Inputs(); // Handle inputs

        float currentTime = glfwGetTime() - startTime; // Get current time since start
        ctx.game_time = currentTime; // Update game time in context

        // std::cout << "Current Time: " << (1/(currentTime-previoius_time)) << " milliseconds" << std::endl;

        // previoius_time= currentTime; // Store previous time for debugging

        // Play click sounds at beat times
        // if (beatIndex < beats.size() && currentTime >= beats[beatIndex]) {
        //     ctx.audio_manager->play(clickPath, 1.0f); // Play click sound
        //     lastClickTime = beats[beatIndex];
        //     beatIndex++;
        // }

        float start_time= std::chrono::duration<float>(std::chrono::high_resolution_clock::now().time_since_epoch()).count(); // Get start time for rendering
        ctx.renderer->render(*ctx.beatmap, currentTime, *ctx.animations); // Render the beatmap and animations
        float render_end_time = std::chrono::duration<float>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()-start_time;
        std::cout<<"render time " << render_end_time << " seconds" << std::endl; // Print render time for debugging

        ctx.animations->update(currentTime); // Update animations

    }



    // Cleanup
    // ctx.audio = new Audio_Manager(); //works fine alone 
    // ctx.renderer = new Renderer(1280, 720); 
    // ctx.animations = new Animations();
    // ctx.beatmap = new Beatmap({}, {}); // Initialize with empty vectors
    // ctx.input_manager = new Input_Manager(ctx.renderer->get_window(), ctx.audio);
    // ctx.game_session = new Game_Session(ctx.beatmap, ctx.audio, ctx.renderer, ctx.animations);

    // ctx.input_manager->set_game_session(ctx.game_session); // Link game session to input manager



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

