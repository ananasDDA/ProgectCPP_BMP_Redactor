#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "Reader.h"
#include "Utils.h"
#include "Parser.h"
#include "Writer.h"
#include "color.h"
#include "image.h"
#include "filter.h"

std::vector<parse::Token> GetTokens(int argc, char** argv);  // NOLINT
Image GetImage(const std::string& path);
void WriteImage(const Image& image, const std::string& path);

Image ApplyFilters(Image& image, const std::vector<parse::Token>& tokens);

#endif  // IMAGEPROCESSOR_H