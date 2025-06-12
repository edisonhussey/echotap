#include <vector>
#include <cmath>
#include <algorithm>
#include <random>

#include "filter_beats.h"

// Assumes beats is a sorted vector of timestamps in seconds
std::vector<float> filter_raw_beats(const std::vector<float>& beats, int maxTaps, float minSpacingSeconds) {
    if (beats.empty()) return {};

    std::vector<float> selected;
    float lastSelected = -minSpacingSeconds; // So first beat is eligible

    for (float beatTime : beats) {
        if (beatTime - lastSelected >= minSpacingSeconds) {
            selected.push_back(beatTime);
            lastSelected = beatTime;
        }
        if (selected.size() >= maxTaps) break;
    }

    return selected;
}
