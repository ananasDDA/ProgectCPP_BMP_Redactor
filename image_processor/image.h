#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <cstddef>
#include <vector>

#include "color.h"

class Image {
public:
    Image() = default;
    Image(size_t in_width, size_t in_height);
    Image(const std::vector<std::vector<Color>>& pixels);  // NOLINT
    Image(const Image& other);
    ~Image() = default;

    size_t GetWidth() const;
    size_t GetHeight() const;
    const std::vector<std::vector<Color>>& GetPixels() const;
    Color& GetPixel(size_t x, size_t y);
    const Color& GetPixel(size_t x, size_t y) const;
    void SetPixel(size_t x, size_t y, const Color& color);

private:
    size_t width_ = 0;
    size_t height_ = 0;
    std::vector<std::vector<Color>> pixs_;  // NOLINT

    void CheckHeightAndWidth(size_t x, size_t y) const;
};

#endif  // IMAGE_H