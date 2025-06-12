#include "next_position.h"
#include <cmath>
#include <cstdlib>
#include <algorithm>
//to initialize random positions
next_position::next_position() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    previous_positions[0] = 0.5f; // x1
    previous_positions[1] = 0.5f; // y1
    previous_positions[2] = 0.6f; // x2
    previous_positions[3] = 0.5f; // y2
}

next_position::~next_position() {}

std::vector<float> next_position::calculate_direction() const {
    float dx = previous_positions[2] - previous_positions[0];
    float dy = previous_positions[3] - previous_positions[1];
    float length = std::sqrt(dx * dx + dy * dy);
    if (length == 0.0f) return {1.0f, 0.0f}; // fallback to rightward
    return {dx / length, dy / length};
}

void next_position::update_previous(const std::vector<float>& new_pos) {
    previous_positions[0] = previous_positions[2];
    previous_positions[1] = previous_positions[3];
    previous_positions[2] = new_pos[0];
    previous_positions[3] = new_pos[1];
}



std::vector<float> next_position::get_next_position() {
    if (mode == 0) {
        float angle = (static_cast<float>(rand()) / RAND_MAX * 2.0f - 1.0f) * (30.0f * M_PI / 180.0f);

        float xDif = previous_positions[2] - previous_positions[0];
        float yDif = previous_positions[3] - previous_positions[1];

        // Normalize vector and scale to fixed length 0.05
        float length = std::sqrt(xDif * xDif + yDif * yDif);
        if (length == 0) length = 0.001f; // avoid div by zero
        xDif = (xDif / length) * 0.05f;
        yDif = (yDif / length) * 0.05f;

        // Rotate vector by angle
        float rotatedX = xDif * cos(angle) - yDif * sin(angle);
        float rotatedY = xDif * sin(angle) + yDif * cos(angle);

        float nextX = previous_positions[2] + rotatedX;
        float nextY = previous_positions[3] + rotatedY;

        // Bounce logic for x
        if (nextX < 0.1f) {
            nextX = 0.1f + (0.1f - nextX);
            rotatedX = -rotatedX;
        }
        else if (nextX > 0.9f) {
            nextX = 0.9f - (nextX - 0.9f);
            rotatedX = -rotatedX;
        }

        // Bounce logic for y (original)
        if (nextY < 0.1f) {
            nextY = 0.1f + (0.1f - nextY);
            rotatedY = -rotatedY;
        }
        else if (nextY > 0.9f) {
            nextY = 0.9f - (nextY - 0.9f);
            rotatedY = -rotatedY;
        }

        // Additional bounce for y < 0.2 to keep out of that bottom region
        if (nextY < 0.2f) {
            nextY = 0.2f + (0.2f - nextY);
            rotatedY = -rotatedY;
        }

        // Update previous positions
        previous_positions[0] = previous_positions[2];
        previous_positions[1] = previous_positions[3];
        previous_positions[2] = nextX;
        previous_positions[3] = nextY;

        return {nextX, nextY};
    }
    else {
        return {0, 0};
    }
}

