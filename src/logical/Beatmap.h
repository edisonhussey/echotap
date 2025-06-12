#ifndef BEATMAP_H
#define BEATMAP_H

#include <vector>
#include <string>
#include <iostream>

#include "Tap.h"
#include "Prompt.h" // Assume these are in separate headers

class Beatmap {
public:
    Beatmap(std::vector<Tap> Taps_, std::vector<Prompt> Prompts_);

    void print() const;

    // std::vector<Tap> getTapsInWindow(float startTime, float endTime) const;
    std::vector<std::reference_wrapper<Tap>> get_taps_in_window_reference(float startTime, float endTime);
    std::vector<Tap> getTapsInWindow(float startTime, float endTime) const;

    std::vector<Prompt> getPromptsInWindow(float startTime, float endTime) const;

    std::vector<Tap> taps;
    std::vector<Prompt> prompts;
};

#endif // BEATMAP_H
