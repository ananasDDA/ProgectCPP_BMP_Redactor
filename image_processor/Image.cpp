#include "image.h"
#include "color.h"
#include <stdexcept>

Image::Image(size_t in_width, size_t in_height)
    : width_(in_width), height_(in_height), pixs_(in_height, std::vector<Color>(in_width)) {
}

Image::Image(const std::vector<std::vector<Color>>& pixels)
    : width_(pixels.empty() ? 0 : pixels[0].size()), height_(pixels.size()), pixs_(pixels) {
}

Image::Image(const Image& other) = default;

size_t Image::GetWidth() const {
    return width_;
}

size_t Image::GetHeight() const {
    return height_;
}

const std::vector<std::vector<Color>>& Image::GetPixels() const {
    return pixs_;
}

Color& Image::GetPixel(size_t x, size_t y) {
    CheckHeightAndWidth(x, y);
    return pixs_[x][y];
}

const Color& Image::GetPixel(size_t x, size_t y) const {
    CheckHeightAndWidth(x, y);
    return pixs_[x][y];
}

void Image::SetPixel(size_t x, size_t y, const Color& color) {
    CheckHeightAndWidth(x, y);
    pixs_[x][y] = color;
}

void Image::CheckHeightAndWidth(size_t x, size_t y) const {
    if (x >= height_ || y >= width_) {
        throw std::out_of_range("Picture out of range");
    }
}
