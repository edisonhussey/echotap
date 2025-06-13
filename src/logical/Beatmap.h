


#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include "context.h"
#include "Quiz.h"
#include "Tap.h"
#include "Prompt.h"
#include "next_position.h"
#include <algorithm>

class Beatmap {

    public:
        std::vector<Tap> taps; // Vector of Tap objects
        std::vector<Prompt> prompts; // Vector of Prompt objects
        context* ctx; // Pointer to context for additional information

        // Beatmap(context* ctx) : ctx(ctx) {};
        // Beatmap(std::vector<Tap> taps_, std::vector<Prompt> prompts_, context* ctx) : taps(std::move(taps_)), prompts(std::move(prompts_)), ctx(ctx) {}

        Beatmap(std::vector<Tap> taps_, std::vector<Prompt> prompts_, context* ctx);


        void setTaps(std::vector<Tap> taps_);
        void setPrompts(std::vector<Prompt> prompts_);

        void print() const; // Optional: for debugging
        std::vector<Tap> getTapsInWindow(float startTime, float endTime) const;
        std::vector<std::reference_wrapper<Tap>> get_taps_in_window_reference(float startTime, float endTime);
        std::vector<Prompt> getPromptsInWindow(float startTime, float endTime) const;



};