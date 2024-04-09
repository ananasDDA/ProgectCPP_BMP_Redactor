#include "Parser.h"
#include "iostream"

namespace parse {
bool Token::Empty() const {
    return name.empty() && args.empty();
}
void Token::Clear() {
    name.clear();
    args.clear();
}
std::vector<Token> Parse(int argc, char* argv[]) {
    std::vector<Token> tokens;
    Token curr;
    for (size_t i = 0; i < static_cast<size_t>(argc); ++i) {
        std::string str(argv[i]);
        if (i <= 2) {
            curr.name = str;
            tokens.push_back(curr);
            curr.Clear();
        } else {
            if (str.front() == '-') {
                if (!curr.Empty()) {
                    tokens.push_back(curr);
                    curr.Clear();
                }
                curr.name = str;
            } else {
                curr.args.push_back(str);
            }
        }
    }
    if (!curr.Empty()) {
        tokens.push_back(curr);
    }
    return tokens;
}
}  // namespace parse