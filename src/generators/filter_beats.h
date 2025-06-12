// #ifndef FILTER_BEATS_H
// #define FILTER_BEATS_H

// #include <vector>
// #include <string>

// std::vector<float> filter_raw_beats(const std::vector<float>& beats, int maxTaps, float minSpacingSeconds);

// #endif // DETECT_BEATS_H


#ifndef FILTER_BEATS_H
#define FILTER_BEATS_H

#include <vector>

std::vector<float> filter_raw_beats(const std::vector<float>& beats, int maxTaps, float minSpacingSeconds);

#endif // FILTER_BEATS_H
