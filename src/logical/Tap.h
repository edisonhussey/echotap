#ifndef TAP_H
#define TAP_H

#include <color.h>

#include <string>

struct Tap {
    float x;                // normalized horizontal (0.0 - 1.0)
    float y;                // normalized vertical (0.0 - 1.0)
    float start_window;     // earliest allowed hit time (seconds)
    float end_window;       // latest allowed hit time (seconds)
    float perfect_hit_time; // ideal hit time (seconds)
    float actual_hit_time;  // real hit time; -1 if not yet hit
    int target_image_id;    // 0 is none
    int hit_sound_id;       // 0 none, 1 sound, 2 miss sound
    bool is_correct;        // true if tap is correct
    float size;             // radius of warning circle (normalized 0.0 - 1.0)
    int score;              // score, 0 if not hit
    std::string text;       // optional text for tap
    // unsigned char r, g, b, a; // color for rendering (0-255)
    Color color;            // color for rendering (RGBA)
};

#endif // TAP_H
