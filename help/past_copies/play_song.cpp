// #define MINIAUDIO_IMPLEMENTATION
// #include "../dependencies/miniaudio.h"
// #include <iostream>

// int main() {
//     ma_engine engine;
//     ma_result result = ma_engine_init(NULL, &engine);
//     if (result != MA_SUCCESS) {
//         std::cerr << "Failed to init audio engine\n";
//         return -1;
//     }

//     result = ma_engine_play_sound(&engine, "assets/audio/songs/hateRodrigo.wav", NULL);
//     if (result != MA_SUCCESS) {
//         std::cerr << "Failed to play sound\n";
//         ma_engine_uninit(&engine);
//         return -1;
//     }

//     std::cout << "Playing sound, press Enter to exit\n";
//     std::cin.get();

//     ma_engine_uninit(&engine);
//     return 0;
// }

// clang++ src/main.cpp -I../dependencies/miniaudio -std=c++17 -o app