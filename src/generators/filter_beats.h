
#ifndef FILTER_BEATS_H
#define FILTER_BEATS_H

#include <vector>

std::vector<float> filter_raw_beats(const std::vector<float>& beats, int maxTaps, float minSpacingSeconds);

#endif // FILTER_BEATS_H
