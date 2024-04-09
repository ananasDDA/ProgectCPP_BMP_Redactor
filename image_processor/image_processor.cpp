#include <iostream>
#include "ImageProcessor.h"

int main(int argc, char* argv[]) {
    try {
        std::vector<parse::Token> tokens = parse::Parse(argc, argv);
        Image img = GetImage(tokens[1].name);
        img = ApplyFilters(img, tokens);  // NOLINT

        WriteImage(img, tokens[2].name);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

std::vector<parse::Token> GetTokens(int argc, char** argv) {  // NOLINT
    std::vector<parse::Token> tokens = parse::Parse(argc, argv);
    if (tokens.size() < 2) {
        throw std::invalid_argument("Expected more arguments");
    }
    return tokens;
}

Image GetImage(const std::string& path) {
    reading_and_writing::Reader reader(path);
    Image img = reader.Read();
    return img;
}

void WriteImage(const Image& image, const std::string& path) {
    reading_and_writing::Writer writer(path);
    writer.Write(image);
}

Image ApplyFilters(Image& image, const std::vector<parse::Token>& tokens) {
    for (size_t i = 3; i < tokens.size(); ++i) {
        image = filters::CreateFilter(tokens[i])->Apply(image);
    }
    return image;
}