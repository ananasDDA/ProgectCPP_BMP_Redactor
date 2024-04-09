#ifndef UTILS_H
#define UTILS_H

#include <cstddef>
#include <vector>

namespace image::utils {
const size_t BITS_PER_PIXEL = 24;
const int BITS_PER_PIXEL_POSITION = 14;
const int BMP_HEADER_SIZE = 14;
const int BYTES_PER_PIXEL = 3;
const size_t CNT_OF_PLANES = 1;
const size_t CNT_OF_PLANES_POSITION = 12;
const int DIB_HEADER_SIZE = 40;
const int DIB_HEADER_SIZE_POSITION = 0;
const int FORMAT_FIRST_POSITION = 0;
const int FORMAT_SECOND_POSITION = 1;
const int FILE_SIZE_POSITION = 2;
const int HEIGHT_POSITION = 8;
const int PADDING_SIZE = 4;
const int PIXS_ARRAY_OFFSET_POSITION = 10;  // NOLINT
const int PIXELS_SIZE = 24;
const int SIZE_POSITION = 2;
const int WIDTH_POSITION = 4;
const int MAX_COLOR = 255;

const std::vector<char> BMP_SIGNATURE = {'B', 'M'};
const std::vector<size_t> SHIFT_VALUES = {8, 16, 24};
}  // namespace image::utils

#endif  // UTILS_H
