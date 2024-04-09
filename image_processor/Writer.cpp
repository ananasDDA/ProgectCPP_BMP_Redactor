#include "Writer.h"

reading_and_writing::Writer::Writer(std::string path) : path_(std::move(path)) {
}

template <typename T>
void reading_and_writing::Writer::NumToBytes(T num, unsigned char* bytes) {
    *bytes = num;
    for (size_t i = 0; i < image::utils::SHIFT_VALUES.size(); ++i) {
        *(bytes + i + 1) = (num >> image::utils::SHIFT_VALUES[i]) & 0xFF;  // NOLINT
    }
}
void reading_and_writing::Writer::WriteBMPHeader(unsigned char* bmp_header, size_t size) {
    bmp_header[image::utils::FORMAT_FIRST_POSITION] = image::utils::BMP_SIGNATURE[0];
    bmp_header[image::utils::FORMAT_SECOND_POSITION] = image::utils::BMP_SIGNATURE[1];
    NumToBytes(size, bmp_header + image::utils::SIZE_POSITION);
    bmp_header[image::utils::PIXS_ARRAY_OFFSET_POSITION] =
        image::utils::BMP_HEADER_SIZE + image::utils::DIB_HEADER_SIZE;
}

void reading_and_writing::Writer::WriteDIBHeader(unsigned char* dib_header, size_t width, size_t height) {
    dib_header[image::utils::DIB_HEADER_SIZE_POSITION] = image::utils::DIB_HEADER_SIZE;
    NumToBytes(width, dib_header + image::utils::WIDTH_POSITION);
    NumToBytes(height, dib_header + image::utils::HEIGHT_POSITION);
    dib_header[image::utils::CNT_OF_PLANES_POSITION] = image::utils::CNT_OF_PLANES;
    dib_header[image::utils::BITS_PER_PIXEL_POSITION] = image::utils::BITS_PER_PIXEL;
}

void reading_and_writing::Writer::Write(const Image& image) {
    std::ofstream img;
    img.open(path_, std::ios::out | std::ios::binary);
    if (!img.is_open()) {
        throw std::invalid_argument(std::string("Can't open file") + path_);
    }
    const size_t size = image::utils::BMP_HEADER_SIZE + image::utils::DIB_HEADER_SIZE +
                        image.GetWidth() * image.GetHeight() * image::utils::BYTES_PER_PIXEL +
                        GetPaddingSize(image.GetWidth()) * image.GetHeight();
    unsigned char bmp_header[image::utils::BMP_HEADER_SIZE] = {};
    std::fill(bmp_header, bmp_header + image::utils::BMP_HEADER_SIZE, 0);
    WriteBMPHeader(bmp_header, size);

    unsigned char dib_header[image::utils::DIB_HEADER_SIZE] = {};
    std::fill(dib_header, dib_header + image::utils::DIB_HEADER_SIZE, 0);
    WriteDIBHeader(dib_header, image.GetWidth(), image.GetHeight());

    img.write(reinterpret_cast<char*>(bmp_header), image::utils::BMP_HEADER_SIZE);
    img.write(reinterpret_cast<char*>(dib_header), image::utils::DIB_HEADER_SIZE);

    unsigned char empty_pix[image::utils::BYTES_PER_PIXEL] = {0, 0, 0};
    for (size_t i = 0; i < image.GetHeight(); i++) {
        for (size_t j = 0; j < image.GetWidth(); j++) {
            auto blue = static_cast<unsigned char>(image.GetPixel(i, j).blue);
            auto green = static_cast<unsigned char>(image.GetPixel(i, j).green);
            auto red = static_cast<unsigned char>(image.GetPixel(i, j).red);
            unsigned char pix[] = {blue, green, red};
            img.write(reinterpret_cast<char*>(pix), image::utils::BYTES_PER_PIXEL);
        }
        img.write(reinterpret_cast<char*>(empty_pix), GetPaddingSize(image.GetWidth()));  // NOLINT
    }
    img.close();
}