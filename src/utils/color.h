// src/utils/Color.h
// #pragma once

// struct Color {
//     float r, g, b, a;

//     Color() : r(0), g(0), b(0), a(255) {}

//     Color(float red, float green, float blue, float alpha = 1.0f)
//         : r(red), g(green), b(blue), a(alpha) {}
// };


#pragma once

struct Color {
    int r, g, b, a;

    Color() : r(0), g(0), b(0), a(255) {}

    Color(int red, int green, int blue, int alpha = 255)
        : r(red), g(green), b(blue), a(alpha) {}
};
