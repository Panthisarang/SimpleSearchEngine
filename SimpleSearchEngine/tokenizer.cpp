#include "tokenizer.h"
#include <algorithm>
#include <sstream>

std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

std::vector<std::string> tokenize(const std::string& text) {
    std::istringstream stream(text);
    std::string word;
    std::vector<std::string> words;
    while (stream >> word) {
        // Remove punctuation and convert to lowercase
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        words.push_back(toLower(word));
    }
    return words;
}
