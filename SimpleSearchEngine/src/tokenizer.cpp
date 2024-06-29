#include "tokenizer.h"
#include <algorithm>
#include <sstream>
#include <set>

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
        word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
        words.push_back(toLower(word));
    }
    return words;
}

// Simple stemming function (Porter Stemmer can be implemented for better accuracy)
std::string stem(const std::string& word) {
    if (word.length() > 3 && word.substr(word.length() - 2) == "ed") {
        return word.substr(0, word.length() - 2);
    }
    if (word.length() > 3 && word.substr(word.length() - 3) == "ing") {
        return word.substr(0, word.length() - 3);
    }
    return word;
}

// Remove stop words from the list of words
std::vector<std::string> removeStopWords(const std::vector<std::string>& words) {
    std::unordered_set<std::string> stopWords = {"a", "an", "and", "the", "is", "in", "at", "of"};
    std::vector<std::string> filteredWords;
    for (const auto& word : words) {
        if (stopWords.find(word) == stopWords.end()) {
            filteredWords.push_back(word);
        }
    }
    return filteredWords;
}
