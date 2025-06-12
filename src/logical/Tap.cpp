#include "Tap.h"
#include <iostream>

void printTap(const Tap& t) {
    std::cout << "Tap at (" << t.x << ", " << t.y << ") "
              << "| Perfect time: " << t.perfect_hit_time
              << " | Actual time: " << t.actual_hit_time
              << " | Correct: " << (t.is_correct ? "Yes" : "No")
              << " | Score: " << t.score
              << " | Text: " << t.text << "\n";
}
