#include "color.h"

Color::Color(uint8_t in_blue, uint8_t in_green, uint8_t in_red) : blue(in_blue), green(in_green), red(in_red) {
}

void Color::SetColor(uint8_t in_blue, uint8_t in_green, uint8_t in_red) {
    blue = in_blue;
    green = in_green;
    red = in_red;
}
