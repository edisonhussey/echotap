#ifndef PROMPT_H
#define PROMPT_H

#include <string>

struct Prompt {
    float x;                  // Normalized horizontal (0.0 - 1.0)
    float y;                  // Normalized vertical (0.0 - 1.0)
    float start_window;       // Earliest allowed display time (seconds)
    float end_window;         // Latest allowed display time (seconds)
    std::string prompt_text;  // Prompt/question text
    int font_type;            // 0 = default, 1 = bold, 2 = italic
};

#endif // PROMPT_H
