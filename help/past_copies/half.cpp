 // Audio_Manager audio;

    // if (!audio.init()) return -1;

    // std::string musicPath = "assets/audio/songs/hate_rodrigo.wav";
    // std::string clickPath = "assets/audio/click_sounds/hat.wav"; // replace with actual path to click

    // if (!audio.load(clickPath)) return -1;
    // if (!audio.load(musicPath)) return -1;


    // std::vector<float> beats = detect_beats(musicPath, 0.7f);

    // Map_Generator generator;
    // Beatmap beatmap = generator.create_map(0.5f, 0.7f, "assets/images/backgrounds/beatmap_background.png", musicPath, Quiz());
    // beatmap.print(); // Print the generated beatmap for debugging

    // std::cout << "Playing clicks at beat times...\n";

    // audio.play(musicPath,0.1f);


    // float lastTime = 0.0f;
    // for (float beatTime : beats) {
    //     float delay = beatTime - lastTime;
    //     if (delay > 0.0f) {
    //         std::this_thread::sleep_for(std::chrono::duration<float>(delay));
    //     }

    //     audio.play(clickPath,1);
    //     lastTime = beatTime;
    // }

    // std::cout << "Done.\n";

    // std::cin.get();
    // return 0;
