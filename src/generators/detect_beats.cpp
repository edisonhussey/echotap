#include "detect_beats.h"
#include <sndfile.h>
#include <iostream>
#include <cmath>

std::vector<float> detect_beats(const std::string& file_path, float sensitivity) {
    SF_INFO sfInfo;
    SNDFILE* file = sf_open(file_path.c_str(), SFM_READ, &sfInfo);

    if (!file) {
        std::cerr << "Failed to open audio file: " << sf_strerror(file) << std::endl;
        return {};
    }

    int numFrames = sfInfo.frames;
    int sampleRate = sfInfo.samplerate;
    int channels = sfInfo.channels;

    std::vector<float> samples(numFrames * channels);
    sf_readf_float(file, samples.data(), numFrames);
    sf_close(file);

    int windowSize = 1024;
    std::vector<float> envelope;

    for (int i = 0; i + windowSize < numFrames; i += windowSize) {
        float sumSquares = 0.0f;
        for (int j = 0; j < windowSize; ++j) {
            float frameSample = 0.0f;
            for (int c = 0; c < channels; ++c) {
                float sample = samples[(i + j) * channels + c];
                frameSample += sample * sample;
            }
            frameSample /= channels;
            sumSquares += frameSample;
        }
        float rms = std::sqrt(sumSquares / windowSize);
        envelope.push_back(rms);
    }

    float quietThreshold = 0.02f;
    std::vector<float> adjustedEnvelope(envelope.size());
    for (size_t i = 0; i < envelope.size(); ++i) {
        float e = envelope[i];
        adjustedEnvelope[i] = (e < quietThreshold) ? (e * e) : e;
    }

    std::vector<float> smoothed(envelope.size());
    int smoothWindow = 4;
    for (size_t i = 0; i < envelope.size(); ++i) {
        float sum = 0.0f;
        int count = 0;
        for (int j = -smoothWindow; j <= smoothWindow; ++j) {
            int idx = static_cast<int>(i) + j;
            if (idx >= 0 && idx < static_cast<int>(adjustedEnvelope.size())) {
                sum += adjustedEnvelope[idx];
                count++;
            }
        }
        smoothed[i] = sum / count;
    }

    std::vector<float> beatTimes;
    for (size_t i = 1; i + 1 < envelope.size(); ++i) {
        float env = adjustedEnvelope[i];
        float avg = smoothed[i];
        float threshold = avg + (1.0f - sensitivity) * avg;

        if (env > adjustedEnvelope[i - 1] &&
            env > adjustedEnvelope[i + 1] &&
            env > threshold) {
            float timeInSeconds = (i * windowSize) / static_cast<float>(sampleRate);
            beatTimes.push_back(timeInSeconds);
        }
    }

    std::vector<float> finalBeats;
    float minSpacing = 0.15f;
    for (float t : beatTimes) {
        if (finalBeats.empty() || (t - finalBeats.back()) > minSpacing) {
            finalBeats.push_back(t);
        }
    }

    return finalBeats;
}

void print_beats(const std::string& file_path, float sensitivity) {
    auto beats = detect_beats(file_path, sensitivity);
    std::cout << "Beats detected at:\n";
    for (float t : beats) {
        std::cout << t << "s\n";
    }
}
