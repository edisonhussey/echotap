#include "Prompt.h"
#include <iostream>

void printPrompt(const Prompt& p) {
    std::cout << "Prompt: \"" << p.prompt_text << "\" at (" << p.x << ", " << p.y << ") "
              << "| Start: " << p.start_window << ", End: " << p.end_window
              << " | Font: " << p.font_type << "\n";
}
