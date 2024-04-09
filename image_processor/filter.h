#ifndef FILTER_H
#define FILTER_H

#include <algorithm>
#include <memory>
#include <vector>

#include "image.h"
#include "Parser.h"

namespace filters {
class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;
    virtual Image Apply(const Image& image) const = 0;

protected:
    template <typename T>
    std::vector<T> GetPixel(const std::vector<std::vector<T>>& matrix, const Image& image, size_t, size_t y) const;
};

class Sharpening : public Filter {  // NOLINT
public:
    Image Apply(const Image& image) const override;
};

class Crop : public Filter {
public:
    Crop(size_t width, size_t height);
    Image Apply(const Image& image) const override;

private:
    size_t width_;
    size_t height_;
};

class Grayscale : public Filter {
public:
    Image Apply(const Image& image) const override;
};

class Negative : public Filter {
public:
    Image Apply(const Image& image) const override;
};

class EdgeDetection : public Filter {
public:
    EdgeDetection(double threshold);  // NOLINT

    Image Apply(const Image& image) const override;  // NOLINT

private:
    const double threshold_ = 0;
};

uint8_t MyClamp(int color, uint8_t max_color);

std::unique_ptr<filters::Filter> CreateFilter(const parse::Token& name);

}  // namespace filters

#endif  // FILTER_H