#include "Reader.h"
#include "image.h"

reading_and_writing::Reader::Reader(const std::string &path) {
    path_ = path;
}

const size_t reading_and_writing::GetPaddingSize(size_t width) {
    return (image::utils::PADDING_SIZE - (width * image::utils::BYTES_PER_PIXEL) % image::utils::PADDING_SIZE) %
           image::utils::PADDING_SIZE;
}

size_t reading_and_writing::Reader::BytesToNum(unsigned char *bytes) {
    size_t number = *bytes;

    for (size_t i = 0; i < image::utils::SHIFT_VALUES.size(); ++i) {
        number += *(bytes + i + 1) << image::utils::SHIFT_VALUES[i];
    }
    return number;
}

Image reading_and_writing::Reader::Read() {
    unsigned char bmp_header[image::utils::BMP_HEADER_SIZE];
    unsigned char dib_header[image::utils::DIB_HEADER_SIZE];

    std::fstream img;
    img.open(path_, std::ios::in | std::ios::binary);
    if (!img.is_open()) {
        throw std::invalid_argument(std::string("Can't open file") + path_);
    }
    if (errno == EACCES) {
        throw std::invalid_argument(std::string("Permission denied to open file") + path_);
    }
    img.read(reinterpret_cast<char *>(bmp_header), image::utils::BMP_HEADER_SIZE);
    if (bmp_header[0] != image::utils::BMP_SIGNATURE[0] || bmp_header[1] != image::utils::BMP_SIGNATURE[1]) {
        throw std::invalid_argument(std::string("Not a BMP file") + path_);
    }
    try {
        img.read(reinterpret_cast<char *>(dib_header), image::utils::DIB_HEADER_SIZE);
        size_t width = BytesToNum(dib_header + image::utils::WIDTH_POSITION);
        size_t height = BytesToNum(dib_header + image::utils::HEIGHT_POSITION);
        Image image(width, height);
        std::vector<std::vector<Color>> data(height);
        std::vector<Color> row(width);
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                unsigned char pix[image::utils::BYTES_PER_PIXEL];
                img.read(reinterpret_cast<char *>(pix), image::utils::BYTES_PER_PIXEL);
                row[j].SetColor(static_cast<uint8_t>(pix[0]), static_cast<uint8_t>(pix[1]),
                                static_cast<uint8_t>(pix[2]));
            }
            data[i] = row;
            img.ignore(GetPaddingSize(width));  // NOLINT
        }
        image = Image(data);
        img.close();
        return image;

    } catch (std::exception &e) {
        throw std::invalid_argument("Error reading file " + path_ + "\n" + static_cast<std::string>(e.what()));
    }
}