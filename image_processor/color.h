
#ifndef CPP_HSE_COLOR_H
#define CPP_HSE_COLOR_H

#pragma once

#include <cstdint>

struct Color {
    Color() = default;
    Color(uint8_t in_blue, uint8_t in_green, uint8_t in_red);

    void SetColor(uint8_t in_blue, uint8_t in_green, uint8_t in_red);

    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

#endif  // CPP_HSE_COLOR_H
