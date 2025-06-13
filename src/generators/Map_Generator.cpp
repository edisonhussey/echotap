#pragma once


#include "Map_Generator.h"
#include "detect_beats.h" // Include beat detection function
#include "filter_beats.h" // Include beat filtering function
#include "Beatmap.h"
#include "Quiz.h"  // Include quiz definition
#include <algorithm>           // for std::min
#include <vector>
#include <string>
#include <unordered_set>    // for std::unordered_set
#include "next_position.h"


// Constructor
Map_Generator::Map_Generator() {
    // any initialization if needed
}

// Destructor
Map_Generator::~Map_Generator() {
    // any cleanup if needed
}
std::pair<std::vector<Tap>, std::vector<Prompt>> Map_Generator::create_map(
    float difficulty,
    float sensitivity,
    const std::string& backgroundImage,
    const std::string& songFile,
    Quiz question_set
) {
    const int question_count = question_set.length();
    std::vector <float> beats = detect_beats(songFile, sensitivity); //detect beats from song path
    filter_raw_beats(beats, 2*question_count, 2-difficulty); // filter beats based on parameters
    int beat_count = beats.size();

    std::vector<Tap> taps;
    std::vector<Prompt> prompts;

    std::vector<int> question_beat_indices;
    float spacing = static_cast<float>(beat_count) / question_count;

    for (int i = 0; i < question_count; ++i) {
        int index = static_cast<int>(i * spacing);
        if (index >= beat_count) index = beat_count - 1;
        question_beat_indices.push_back(index);
    }

    // Create a set for quick lookup
    std::unordered_set<int> question_set_indices(question_beat_indices.begin(), question_beat_indices.end());

    float some_margin = 1.5;

    next_position position_generator; // Create an instance of next_position
    std::vector<float> new_position;
    // Now iterate through beats and build taps and prompts
    for (int i = 0; i < beat_count; ++i) {
        new_position = position_generator.get_next_position(); // Get next position

        float beat_time = beats[i];
        
        if (question_set_indices.count(i)) {
            // This beat is for a question
            
            question question = question_set.get_next();/* map i to question index? Use i or position in question_beat_indices */
            // std::vector<float> new_position 
            // Add prompt (position, text, etc.)
            Prompt prompt;
            prompt.start_window = beat_time - some_margin;
            prompt.end_window = beat_time;
            prompt.prompt_text = question.prompt;
            prompt.x = 0.5f; // example
            prompt.y = 0.1f; // example
            prompts.push_back(prompt);
     

            // centerX, centerY is your new_position from before
            float centerX = new_position[0];
            float centerY = new_position[1];
            int N = static_cast<int>(question.choices.size());
            float radius = 0.15f;  // distance from center to each tap

            // 1. Compute polygon points
            std::vector<std::pair<float, float>> points;
            for (int i = 0; i < N; ++i) {
                float angle = 2.0f * M_PI * i / N;  // evenly spaced angles
                float px = centerX + radius * cos(angle);
                float py = centerY + radius * sin(angle);
                points.emplace_back(px, py);
            }

            // 2. Check bounds for x and y
            float minX = points[0].first, maxX = points[0].first;
            float minY = points[0].second, maxY = points[0].second;
            for (const auto& p : points) {
                if (p.first < minX) minX = p.first;
                if (p.first > maxX) maxX = p.first;
                if (p.second < minY) minY = p.second;
                if (p.second > maxY) maxY = p.second;
            }

            // 3. Calculate needed shifts to bring all points into [0.1, 0.9]
            float shiftX = 0.0f;
            if (minX < 0.1f) shiftX = 0.1f - minX;
            else if (maxX > 0.9f) shiftX = 0.9f - maxX;

            float shiftY = 0.0f;
            if (minY < 0.1f) shiftY = 0.1f - minY;
            else if (maxY > 0.9f) shiftY = 0.9f - maxY;

            // 4. Apply shift to all points
            for (auto& p : points) {
                p.first += shiftX;
                p.second += shiftY;
            }

            // 5. Now create taps at these points
            for (int c = 0; c < N; ++c) {
                Tap tap;
                tap.perfect_hit_time = beat_time;
                tap.x = points[c].first;
                tap.y = points[c].second;
                tap.is_correct = (c == 0);
                tap.start_window = beat_time - some_margin;
                tap.end_window = beat_time;
                tap.color = {255, 255, 255, 125}; // white and fully opaque
                tap.size = 0.1f;                   // example size
                tap.text = question.choices[c]; // Store choice text in tap
                tap.actual_hit_time = -1.0f; // Initialize actual hit time
                // other tap fields...
                taps.push_back(tap);
}

        } else {
            // Filler tap: single tap without question
            Tap tap;
            tap.perfect_hit_time = beat_time;
            tap.x = new_position[0]; // example center
            tap.y = new_position[1];
            tap.is_correct = true;
            tap.start_window = beat_time-some_margin;
            tap.end_window = beat_time ;
            tap.actual_hit_time = -1.0f; // Initialize actual hit time
            tap.color = {255, 255, 255, 125};  // white and fully opaque
            tap.size = 0.1f; // example size, normalized
            taps.push_back(tap);
        }
    }

    // Beatmap map(taps, prompts);

    // return map; // no extra parentheses
    // return std::pair<std::vector<Tap> , std::vector<Prompt> >(taps, prompts); // Return both taps and prompts
    // return std::pair<Beatmap, Quiz>(Beatmap(taps, prompts), question_set); // Return both Beatmap and Quiz

    // std::pair <std::vector<Tap> , std::vector<Prompt>  > result = std::make_pair(taps, prompts);
    // return result;

    return std::make_pair(taps, prompts);

}

