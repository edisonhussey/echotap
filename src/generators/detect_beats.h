#pragma once
#include <string>
#include <vector>

std::vector<float> detect_beats(const std::string& file_path, float sensitivity = 0.5f);
void print_beats(const std::string& file_path, float sensitivity = 0.5f);
