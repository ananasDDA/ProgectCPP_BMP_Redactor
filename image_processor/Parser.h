#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
namespace parse {
struct Token {
    std::string name;
    std::vector<std::string> args;
    void Clear();
    bool Empty() const;
};

std::vector<Token> Parse(int argc, char* argv[]);
}  // namespace parse

#endif  // PARSER_H
