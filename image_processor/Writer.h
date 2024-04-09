#ifndef WRITER_H
#define WRITER_H

#include <fstream>
#include <string>
#include <algorithm>
#include "image.h"
#include "Reader.h"
#include <utility>
#include "Utils.h"

namespace reading_and_writing {
class Writer {
public:
    Writer(std::string path);  // NOLINT
    void Write(const Image& image);

private:
    void WriteBMPHeader(unsigned char* bmp_header, size_t size);
    void WriteDIBHeader(unsigned char* dib_header, size_t width, size_t height);

    template <typename T>
    void NumToBytes(T num, unsigned char* bytes);

    std::string path_;
};
}  // namespace reading_and_writing

#endif  // WRITER_H