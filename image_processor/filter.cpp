#include "filter.h"
#include "Utils.h"
#include "iostream"

template <typename T>
std::vector<T> filters::Filter::GetPixel(const std::vector<std::vector<T>>& matrix, const Image& image, size_t x,
                                         size_t y) const {
    T blue = 0;
    T green = 0;
    T red = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.front().size(); ++j) {
            blue += image
                        .GetPixel(std::clamp(x + i - 1, static_cast<size_t>(0), image.GetHeight() - 1),
                                  std::clamp(y + j - 1, static_cast<size_t>(0), image.GetWidth() - 1))
                        .blue *
                    matrix[i][j];
            red += image
                       .GetPixel(std::clamp(x + i - 1, static_cast<size_t>(0), image.GetHeight() - 1),
                                 std::clamp(y + j - 1, static_cast<size_t>(0), image.GetWidth() - 1))
                       .red *
                   matrix[i][j];
            green += image
                         .GetPixel(std::clamp(x + i - 1, static_cast<size_t>(0), image.GetHeight() - 1),
                                   std::clamp(y + j - 1, static_cast<size_t>(0), image.GetWidth() - 1))
                         .green *
                     matrix[i][j];
        }
    }
    return {blue, green, red};
}

uint8_t filters::MyClamp(int color, uint8_t max_color = 255) {  // NOLINT
    if (color < 0) {
        return 0;
    } else if (color > max_color) {
        return max_color;
    }
    return static_cast<uint8_t>(color);
}

Image filters::Sharpening::Apply(const Image& image) const {
    std::vector<std::vector<Color>> new_data(image.GetHeight(), std::vector<Color>(image.GetWidth()));
    const std::vector<std::vector<int>> matrix = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            int sum_blue = 0;
            int sum_green = 0;
            int sum_red = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    size_t i = std::clamp(static_cast<int>(y) + dy, 0, static_cast<int>(image.GetHeight()) - 1);
                    size_t j = std::clamp(static_cast<int>(x) + dx, 0, static_cast<int>(image.GetWidth()) - 1);

                    Color pixel = image.GetPixel(i, j);
                    int kernel_value = matrix[dy + 1][dx + 1];

                    sum_blue += pixel.blue * kernel_value;
                    sum_green += pixel.green * kernel_value;
                    sum_red += pixel.red * kernel_value;
                }
            }

            Color& new_pixel = new_data[y][x];
            new_pixel.blue = MyClamp(sum_blue);
            new_pixel.green = MyClamp(sum_green);
            new_pixel.red = MyClamp(sum_red);
        }
    }

    return {new_data};
}

filters::EdgeDetection::EdgeDetection(double threshold) : threshold_(threshold) {
}  // NOLINT

Image filters::EdgeDetection::Apply(const Image& image) const {
    std::vector<std::vector<double>> gs_data(image.GetHeight(), std::vector<double>(image.GetWidth()));
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            Color old_value = image.GetPixel(i, j);
            double pixel = 0.299f * old_value.red + 0.587f * old_value.green + 0.114f * old_value.blue;  // NOLINT
            gs_data[i][j] = pixel;
        }
    }
    const std::vector<std::vector<double>> matrix = {{0.0f, -1.0f, 0.0f}, {-1.0f, 4.0f, -1.0f}, {0.0f, -1.0f, 0.0f}};
    std::vector<std::vector<double>> edge_data(image.GetHeight(), std::vector<double>(image.GetWidth(), 0));

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            double sum_color = 0;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    size_t i = std::clamp(static_cast<int>(y) + dy, 0, static_cast<int>(image.GetHeight()) - 1);
                    size_t j = std::clamp(static_cast<int>(x) + dx, 0, static_cast<int>(image.GetWidth()) - 1);

                    double kernel_value = matrix[dy + 1][dx + 1];
                    sum_color += gs_data[i][j] * kernel_value;
                }
            }
            edge_data[y][x] = sum_color;
        }
    }
    Image result(image.GetWidth(), image.GetHeight());
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Color new_color = (edge_data[y][x] > threshold_)  // NOLINT
                                  ? Color(image::utils::MAX_COLOR, image::utils::MAX_COLOR, image::utils::MAX_COLOR)
                                  : Color(0, 0, 0);
            result.SetPixel(y, x, new_color);  // NOLINT
        }
    }
    return result;
}

filters::Crop::Crop(size_t width, size_t height) : width_(width), height_(height) {
}
Image filters::Crop::Apply(const Image& image) const {
    Image new_image(std::min(width_, image.GetWidth()), std::min(height_, image.GetHeight()));
    for (size_t i = image.GetHeight() - std::min(height_, image.GetHeight()); i < image.GetHeight(); ++i) {
        std::vector<Color> row(std::min(width_, image.GetWidth()));
        for (size_t j = 0; j < std::min(width_, image.GetWidth()); ++j) {
            new_image.SetPixel(i - (image.GetHeight() - std::min(height_, image.GetHeight())), j, image.GetPixel(i, j));
        }
    }
    return new_image;
}

Image filters::Grayscale::Apply(const Image& image) const {
    Image result = image;
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            auto& pixel = result.GetPixel(i, j);
            uint8_t gray =
                static_cast<uint8_t>(0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue);  // NOLINT
            pixel = Color(gray, gray, gray);
        }
    }
    return result;
}

Image filters::Negative::Apply(const Image& image) const {
    Image result = image;
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            auto& pixel = result.GetPixel(i, j);
            pixel.red = 255 - pixel.red;      // NOLINT
            pixel.green = 255 - pixel.green;  // NOLINT
            pixel.blue = 255 - pixel.blue;    // NOLINT
        }
    }
    return result;
}

std::unique_ptr<filters::Filter> filters::CreateFilter(const parse::Token& token) {
    const std::string& filter = token.name;
    if (filter == "-sharp") {
        if (!token.args.empty()) {
            throw std::invalid_argument("The sharpening filter does not accept any arguments");
        }
        return std::make_unique<filters::Sharpening>();
    } else if (filter == "-crop") {
        if (token.args.size() != 2) {
            throw std::invalid_argument("The crop filter requires exactly two arguments: width and height");
        }
        try {
            size_t width = std::stoull(token.args[0]);
            size_t height = std::stoull(token.args[1]);
            return std::make_unique<filters::Crop>(width, height);
        } catch (const std::exception& e) {
            throw std::invalid_argument("Invalid argument for crop filter. Both width and height need to be numbers.");
        }
    } else if (filter == "-gs") {
        if (!token.args.empty()) {
            throw std::invalid_argument("The grayscale filter does not accept any arguments");
        }
        return std::make_unique<filters::Grayscale>();
    } else if (filter == "-neg") {
        if (!token.args.empty()) {
            throw std::invalid_argument("The negative filter does not accept any arguments");
        }
        return std::make_unique<filters::Negative>();
    } else if (filter == "-edge") {
        if (token.args.size() != 1) {
            throw std::invalid_argument("The edge detection filter requires exactly one argument: threshold");
        }
        try {
            double threshold = std::stod(token.args[0]);
            return std::make_unique<filters::EdgeDetection>(image::utils::MAX_COLOR * threshold);
        } catch (const std::exception& e) {
            throw std::invalid_argument("Invalid argument for edge detection filter. Threshold needs to be a number.");
        }
    } else {
        throw std::invalid_argument("Unknown filter: " + filter);
    }
}
