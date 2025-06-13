#pragma once
#include "Beatmap.h"
#include <algorithm>
#include <iostream> // for std::cout
#include "Tap.h"
#include "Prompt.h"
#include <utility>
// Constructor
// Beatmap::Beatmap(std::vector<Tap> taps_, std::vector<Prompt> prompts_, context* context)
//     : taps(std::move(taps_)), prompts(std::move(prompts_)), ctx(context)
// {

Beatmap::Beatmap(std::vector<Tap> taps_, std::vector<Prompt> prompts_, context* context)
    : taps(std::move(taps_)), prompts(std::move(prompts_)), ctx(context)
{}


//     std::sort(taps.begin(), taps.end(), [](const Tap& a, const Tap& b) {
//         return a.perfect_hit_time < b.perfect_hit_time;
//     });

//     std::sort(prompts.begin(), prompts.end(), [](const Prompt& a, const Prompt& b) {
//         return a.start_window < b.start_window;
//     });
// }

// Beatmap::Beatmap(std::vector<Tap> taps_, std::vector<Prompt> prompts_, context* context)
//     : taps(std::move(taps_)), prompts(std::move(prompts_)), ctx(context)
// {
//     // No sorting here
// }


// Print beatmap contents (optional)
void Beatmap::print() const {
    for (const auto& t : taps) {
        std::cout << "Tap at (" << t.x << ", " << t.y << ") | Time: " << t.perfect_hit_time << "\n";
    }
    for (const auto& p : prompts) {
        std::cout << "Prompt: " << p.prompt_text << " | Time: " << p.start_window << "\n";
    }
}

void Beatmap::setTaps(std::vector<Tap> taps_) {
    taps = std::move(taps_);
    std::sort(taps.begin(), taps.end(), [](const Tap& a, const Tap& b) {
        return a.perfect_hit_time < b.perfect_hit_time;

    });
}

void Beatmap::setPrompts(std::vector<Prompt> prompts_) {
    prompts = std::move(prompts_);
    std::sort(prompts.begin(), prompts.end(), [](const Prompt& a, const Prompt& b) {
        return a.start_window < b.start_window;
    });
}



std::vector<Tap> Beatmap::getTapsInWindow(float startTime, float endTime) const {
    std::vector<Tap> result;
    std::copy_if(taps.begin(), taps.end(), std::back_inserter(result),
                 [startTime, endTime](const Tap& t) {
                     return (t.start_window <= endTime) && (t.end_window >= startTime);
                 });
    return result;
}




// std::vector<std::reference_wrapper<Tap>> Beatmap::get_taps_in_window_reference(float startTime, float endTime) {
//     std::vector<std::reference_wrapper<Tap>> result;
//     for (Tap& t : taps) {
//         if (t.start_window <= endTime && t.end_window >= startTime) {
//             result.push_back(std::ref(t));
//         }
//     }
//     return result;
// }

std::vector<std::reference_wrapper<Tap>> Beatmap::get_taps_in_window_reference(float startTime, float endTime) {
    std::vector<std::reference_wrapper<Tap>> result;
    for (Tap& t : taps) {
        if (t.start_window <= endTime && t.end_window >= startTime) {
            result.push_back(std::ref(t));
        }
    }
    // Sort by perfect_hit_time, latest to earliest
    std::sort(result.begin(), result.end(), 
        [](const std::reference_wrapper<Tap>& a, const std::reference_wrapper<Tap>& b) {
            return a.get().perfect_hit_time > b.get().perfect_hit_time; // Latest first
        });
    return result;
}


// Get prompts in a time window
std::vector<Prompt> Beatmap::getPromptsInWindow(float startTime, float endTime) const {
    std::vector<Prompt> result;
    std::copy_if(prompts.begin(), prompts.end(), std::back_inserter(result),
                 [startTime, endTime](const Prompt& p) {
                     return (p.start_window <= endTime) && (p.end_window >= startTime);
                 });
    return result;
}
