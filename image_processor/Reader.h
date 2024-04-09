#ifndef READER_H
#define READER_H
#include <string>
#include <fstream>
#include <cerrno>
#include "Utils.h"
#include "image.h"

namespace reading_and_writing {
class Reader {
public:
    Reader(const std::string &path);  // NOLINT

    Image Read();

private:
    std::string path_;

    size_t BytesToNum(unsigned char *bytes);
};

const size_t GetPaddingSize(size_t width);
}  // namespace reading_and_writing

#endif  // READER_H
